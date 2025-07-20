#version 330

#ifdef GL_ES
precision highp float;
#endif

#define MAX_DIST 100.0
#define MAX_GROUPS 128

const vec3 voxel_pos[8] = vec3[8](
	vec3(-1, -1, -1),
	vec3(-1, -1, 1),
	vec3(-1, 1, -1),
	vec3(-1, 1, 1),
	vec3(1, -1, -1),
	vec3(1, -1, 1),
	vec3(1, 1, -1),
	vec3(1, 1, 1),
);

struct intersection {
	vec3 color;
	vec3 p;
};

struct node {
	bool free;
	vec3 color;
	int child;
};

struct node_group {
	int parent;
	node nodes[8];
};
 
uniform vec2 u_resolution;
uniform vec3 u_camera_pos;
uniform vec3 u_camera_dir;
uniform node_group u_groups[MAX_GROUPS];

vec2 box(in vec3 ro, in vec3 rd, vec3 size) 
{
	vec3 m = 1.0 / rd;
	vec3 n = m * ro;
	vec3 k = abs(m) * size;

	vec3 t1 = -n - k;
	vec3 t2 = -n + k;

	float tN = max(max(t1.x, t1.y), t1.z);
	float tF = min(min(t2.x, t2.y), t2.z);

	if(tN > tF || tF < 0.0) return vec2(-1.0);

	return vec2(tN, tF);
}

intersection intersect_with_svo(vec3 ro, vec3 rd)
{
	int id      = 0;
	vec3 size   = vec3(0.5);
	vec3 off    = vec3(0.0);
	int clipped = -1;

	while (true) {
		vec2 min_it = vec2(MAX_DIST);
		vec2 it;
		bool is_intersected = false;
		node intersected_node;
		int intersected_i;
		vec3 p;

		for (int i = 0; i < 8; i++) {
			if (clipped != -1 && clipped == i) {
				clipped = -1;
				continue;
			}

			node crnt_node = u_groups[id].nodes[i];

			if (crnt_node.free)
				continue;

			it = box(ro - (voxel_pos[i] * size + off), rd, size);

			if (it.x > 0.0 && it.x < min_it.x) {
				min_it           = it;
				intersected_node = crnt_node;
				is_intersected   = true;
				p                = ro + rd * it.x;
				intersected_i    = i;
			}
		}

		off += size * voxel_pos[intersected_i];

		if (!is_intersected && id == 0)
			return intersection(vec3(0.0), vec3(0.0));

		if (!is_intersected) {
			id      = u_groups[id].parent;
			clipped = intersected_i;

			size *= 2.0;
			off -= size * voxel_pos[intersected_i];

			continue;
		}

		if (is_intersected && intersected_node.child != -1)
			id = intersected_node.child;

		if (is_intersected && intersected_node.child == -1)
			return intersection(intersected_node.color, p);

		size /= 2.0;
	}
}
 
void main()
{
	vec2 uv = (gl_FragCoord.xy * 2.0 - u_resolution) / u_resolution.y;
	vec3 ro = u_camera_pos;
	vec3 rd = normalize(vec3(uv, 1.0));

	gl_FragColor = vec4(intersect_with_svo(ro, rd).color, 1.0);
} 
