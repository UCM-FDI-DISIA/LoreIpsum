
#pragma once

#ifdef _DEBUG
//#include <iostream>
#endif // DEBUG


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
#ifdef _DEBUG
			//std::cout << "Update cmp: " << updateId << '\n';
#endif // DEBUG
			return myUpdateId;
		}

	}

	template<typename T>
	static int getRenderId() {
		if (std::is_base_of<ComponentRender, T>::value) {
			static int myRenderId = renderId++;
#ifdef _DEBUG
			//std::cout << "Render cmp: " << renderId << '\n';
#endif // DEBUG
			return myRenderId;
		}
	}

private:
	static int updateId;
	static int renderId;

};

//int GenID::updateId = 0;
//int GenID::renderId = 0;
