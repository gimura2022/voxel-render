#include <cstdint>
#include <ranges>
#include <string>
#include <vector>

#include <SFML/Graphics/Glsl.hpp>

#include "svo.hpp"
#include "utils.hpp"

namespace svo {

void Node::set_in_shader(str_t&& uniform_name, sf::Shader& shader) const
{
	const auto glsl_view = get_glsl_view();

	// FIXME: use std::views::enumerate instead
	for (auto i = 0; i < glsl_view.size(); i++) {
		const auto& glsl_group = glsl_view[i];

		shader.setUniform(uniform_name + "[" + std::to_string(i) + "].parent", glsl_group.parent);

		for (auto j = 0; j < NODE_CHILD_COUNT; j++) {
			const auto set_node_param = [&] <typename T> (str_t&& param, T value) -> void {
				shader.setUniform(uniform_name + "[" + std::to_string(i) + "].nodes["
					+ std::to_string(j) + "]." + param, value);
			};

			const auto& node = glsl_group.nodes[j];

			set_node_param("free", node.free);
			set_node_param("child", node.child);
			set_node_param("color", sf::Glsl::Vec3(node.color[0], node.color[1], node.color[2]));
		}
	}
}

const std::vector<glsl_node_group> Node::get_glsl_view() const
{
	if (leaf)
		error("leaf node can't be translated to glsl view");

	auto recursive_build = [] (int parent, const Node& node, std::vector<glsl_node_group>& groups,
			auto&& recursive_build) -> int {
		const auto build_node = [] (const Node& node, int child) -> glsl_node {
			return {
				.free = node.is_free(),
				.color = {
					node.get_color().r / 255.f,
					node.get_color().g / 255.f,
					node.get_color().b / 255.f
				},
				.child = child,
			};
		};

		if (node.is_leaf())
			return -1;

		const auto crnt_id = groups.size();

		groups.push_back({ parent });

		for (auto i = 0; i < NODE_CHILD_COUNT; i++) {
			const auto& child   = node.get_nodes()[i];
			const auto child_id =
				recursive_build(crnt_id, *child, groups, recursive_build);

			groups[crnt_id].nodes[i] = build_node(*child, child_id);
		}

		return crnt_id;
	};

	std::vector<glsl_node_group> groups;
	recursive_build(-1, *this, groups, recursive_build);

	return std::move(groups);
}

sf::Color Node::get_color() const
{
	if (leaf)
		return color;
	else {
		std::uint8_t r, g, b;
		auto count = 0;

		for (const auto& node : nodes) {
			if (node->is_free())
				continue;

			r += node->get_color().r;
			g += node->get_color().g;
			b += node->get_color().b;

			count++;
		}

		r /= count;
		g /= count;
		b /= count;

		return sf::Color(r, g, b);
	}
}

}

