#include "../pch.h"
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
	static void ConfirmationPopUp();

	//para llamar a decisionFactory
	static Factory* factory;

	/// En funcion del indice, devuelve el callback del efecto
	///	*** Esto es terrible, quiero que sirva para salir al paso
	///	y como concepto inicial ***

	static std::function<void()> callEvent(
		int index, int scene)
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
			return []
				{
					ConfirmationPopUp();
				};
		default:
			return nullptr;
		}
	}
};
