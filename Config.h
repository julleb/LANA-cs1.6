#ifndef CONFIG_H
#define CONFIG_H

namespace Config {

	struct Config {
		bool aim;
		bool esp;
		float fov;
		int smooth;
		Config() {
			aim = 1;
			esp = 1;
			fov = 2.0f;
			smooth = 4;
		}
	};
	extern Config config;
}


#endif