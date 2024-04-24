#include <../pchs/pch.h>

#include "../Namespaces.h"

class Factory;

class DialogueEventCollection
{
public:
	DialogueEventCollection();

	// ChangeScene
	static void ChangeScene(int scene);

	//StartAnimation
	static void StartAnimation();

	//ConfirmationPopUp
	static void ConfirmationPopUp(ecs::entity_t parent);

	//ActionEnded
	static void ActionEnded();

	//para llamar a decisionFactory
	Factory* factory;

	/// En funcion del indice, devuelve el callback del efecto
	///	*** Esto es terrible, quiero que sirva para salir al paso
	///	y como concepto inicial ***

	static std::function<void()> callEvent(
		int index, int scene, ecs::entity_t parent)
	{
		switch (index)
		{
		case DialogueEvents::None:
			return []
			{
			};
		case DialogueEvents::ChangeScene:
			return [scene]
			{
				ChangeScene(scene);
			};

			break;
		case DialogueEvents::StartAnimation:
			return []
			{
			};
		case DialogueEvents::ConfirmMatchPopUp:
			return [parent]
			{
				ConfirmationPopUp(parent);
			};
		case DialogueEvents::ActionEnded:
			return []
			{
				ActionEnded();
			};
		default:
			return nullptr;
		}
	}
};
