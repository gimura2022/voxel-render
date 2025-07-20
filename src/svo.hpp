#ifndef _svo_h
#define _svo_h

#include <array>
#include <string>
#include <type_traits>
#include <memory>
#include <vector>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Shader.hpp>

#include "defs.hpp"

namespace svo {

inline constexpr auto NODE_CHILD_COUNT = 8;

struct glsl_node {
	bool free;
	float color[3];
	int child;
};

struct glsl_node_group {
	int parent;
	glsl_node nodes[NODE_CHILD_COUNT];
};

class Node {
	using nodes_t = std::array<std::unique_ptr<Node>, NODE_CHILD_COUNT>;

public:
	explicit inline Node(nodes_t&& nodes)
		: Node(std::move(nodes), sf::Color::Black, false, false) {}
	explicit inline Node(sf::Color color)
		: Node({}, color, false, true) {}
	inline Node()
		: Node({}, sf::Color::Black, true, true) {}

	void set_in_shader(str_t&& uniform_name, sf::Shader& shader) const;

	sf::Color get_color() const;

	inline const nodes_t& get_nodes() const
	{
		return nodes;
	}

	inline bool is_free() const
	{
		return free;
	}

	inline bool is_leaf() const
	{
		return leaf;
	}

private:
	inline Node(nodes_t&& nodes, sf::Color color, bool free, bool leaf)
		: nodes(std::move(nodes)), color(color), free(free), leaf(leaf) {}

	const std::vector<glsl_node_group> get_glsl_view() const;

	nodes_t nodes;

	sf::Color color;
	bool free, leaf;
};

}

#endif
