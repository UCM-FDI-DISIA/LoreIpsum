
#pragma once

#include <iostream>
#include <type_traits>

class ComponentUpdate;
class ComponentRender;

class GenID {
public:
	GenID();
	virtual ~GenID();

	template<typename T>
	static int getUpdateId() {
		
		if (std::is_base_of<ComponentUpdate, T>::value) {
			static int myUpdateId = updateId++;
			std::cout << "Update cmp: " << updateId << std::endl;
			return myUpdateId;
		}

	}

	template<typename T>
	static int getRenderId() {
		if (std::is_base_of<ComponentRender, T>::value) {
			static int myRenderId = renderId++;
			std::cout << "Render cmp: " << renderId << std::endl;
			return myRenderId;
		}
	}

private:
	static int updateId;
	static int renderId;

};

//int GenID::updateId = 0;
//int GenID::renderId = 0;
