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


	/*template<typename ...Ts>
	void SetFactories(CardFactory* cf, Ts &&... args) {
		cardFactory = cf;
		SetFactories(std::forward<Ts>(args)...);
	}*/


	/// En funcion del indice, devuelve el callback del efecto
	///	*** Esto es terrible, quiero que sirva para salir al paso
	///	y como concepto inicial ***
	template<typename ...Ts>
	static std::function<void()> callEvent(
		DialogueEvents::Events index,
		Ts &&... args)
	{
		switch (index)
		{
		case DialogueEvents::None:
			return [std::forward<Ts>(args)...]
				{
					ChangeScene(std::forward<Ts>(args)...);
				};
		case DialogueEvents::ChangeScene:
			return [std::forward<Ts>(args)...]
				{

				};
		case DialogueEvents::StartAnimation:
			return [std::forward<Ts>(args)...]
				{

				};
		case DialogueEvents::ConfirmMatchPopUp:
			return [std::forward<Ts>(args)...]
				{

				};
		default:
			return nullptr;
		}
	}
};
