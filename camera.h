#ifndef _camera_h
#define _camera_h

#include <SFML/System/Vector3.hpp>

class Camera {
public:
	static inline constexpr auto SPEED     = 3.0;
	static inline constexpr auto ROT_SPEED = 0.8;

	inline Camera(sf::Vector3f dir, sf::Vector3f pos) : dir(dir), pos(pos) {}

	void update(double delta);

	inline const sf::Vector3f& get_pos() const
	{
		return pos;
	}

	inline const sf::Vector3f& get_dir() const
	{
		return dir;
	}

private:
	sf::Vector3f dir, pos;
};

#endif
