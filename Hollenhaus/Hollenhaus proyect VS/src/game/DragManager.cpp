#include "DragManager.h"
#include "../sdlutils/InputHandler.h"

DragManager::DragManager()
{
}

DragManager::~DragManager()
{
}

void DragManager::initComponent()
{
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { OnLeftClickDown(); });
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_UP, [this] { OnLeftClickUp(); });
}

void DragManager::update()
{
	//si tenemos carta drageada...
	
	//actualizamos su posicion teniendo en cuenta la posicion del raton



}

void DragManager::OnLeftClickDown()
{
	//buscar una colision con una entidad del grupo carta(teniendo en cuenta el order in layer)

	//si encuentra una, esa entidad pasa a ser el transform draged

	//se guarda la posicion/ transform de como estaba la carta


}

void DragManager::OnLeftClickUp()
{
	//si no tenemos carta drageada, no hacemos nada

	//si, sí la tenemos, verifcamos colisiones con el grupo DropDetector

	//si tenemos una colision con el drop detector, cambiamos la posicion de la carta por la que guarde el drop

	//sino, devolvemos la carta a su posicion inicial

	//en cualquier caso, ya no tenemos carta drageada

}
