#include "../pch.h"
#include "../Namespaces.h"



class DialogueEventCollection
{
public:
	DialogueEventCollection();

	// ChangeScene
	static void ChangeScene(int scene);

	//StartAnimation
	static void StartAnimation();

	//ConfirmationPopUp
	static bool ConfirmationPopUp();


	/// En funcion del indice, devuelve el callback del efecto
	///	*** Esto es terrible, quiero que sirva para salir al paso
	///	y como concepto inicial ***
	static std::function<void()> getEvent(
		DialogueEvents::Events index)
	{
		switch (index)
		{
		case DialogueEvents::None:
			return []
				{
					//ChangeScene(scene);
				};
		case DialogueEvents::ChangeScene:
			return []
				{

				};
		case DialogueEvents::StartAnimation:
			return []
				{

				};
		case DialogueEvents::ConfirmMatchPopUp:
			return []
				{

				};
		default:
			return nullptr;
		}
	}
};
