#include "DialogueBlueprintLibrary.h"
#include "EngineUtils.h"

void UDialogueBlueprintLibrary::WaitInput(UObject* WorldContextObject, FLatentActionInfo LatentInfo)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		FLatentActionManager& LatentManager = World->GetLatentActionManager();

		struct FInputAction : public FPendingLatentAction
		{
		public:
			TWeakObjectPtr<ADialogueActor> DialogueActor;
			FName ExecutionFunction;
			int32 OutputLink;
			FWeakObjectPtr CallbackTarget;

			FInputAction(ADialogueActor* InDialogue, const FLatentActionInfo& InLatentInfo)
			{
				DialogueActor = InDialogue;
				ExecutionFunction = InLatentInfo.ExecutionFunction;
				OutputLink = InLatentInfo.Linkage;
				CallbackTarget = InLatentInfo.CallbackTarget;
			}
			void UpdateOperation(FLatentResponse& Response) override
			{
				const bool bInput = DialogueActor.IsValid() && DialogueActor->bInput;
				Response.FinishAndTriggerIf(bInput, ExecutionFunction, OutputLink, CallbackTarget);
				if (bInput)
				{
					DialogueActor->bInput = false;
				}
			}
		};

		FInputAction* NewAction = new FInputAction(GetCurrentDialogueActor(World), LatentInfo);
		LatentManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, NewAction);
	}
}

FString UDialogueBlueprintLibrary::WaitSelect(UObject* WorldContextObject, FLatentActionInfo LatentInfo)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		FLatentActionManager& LatentManager = World->GetLatentActionManager();

		struct FSelectAction : public FPendingLatentAction
		{
		public:
			TWeakObjectPtr<ADialogueActor> DialogueActor;
			FName ExecutionFunction;
			int32 OutputLink;
			FWeakObjectPtr CallbackTarget;

			FSelectAction(ADialogueActor* InDialogue, const FLatentActionInfo& InLatentInfo)
			{
				DialogueActor = InDialogue;
				ExecutionFunction = InLatentInfo.ExecutionFunction;
				OutputLink = InLatentInfo.Linkage;
				CallbackTarget = InLatentInfo.CallbackTarget;
			}
			void UpdateOperation(FLatentResponse& Response) override
			{
				const bool bInput = DialogueActor.IsValid() && DialogueActor->bInput;
				Response.FinishAndTriggerIf(bInput, ExecutionFunction, OutputLink, CallbackTarget);
				if (bInput)
				{
					DialogueActor->bInput = false;
				}
			}
		};

		FSelectAction* NewAction = new FSelectAction(GetCurrentDialogueActor(World), LatentInfo);
		LatentManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, NewAction);
	}
	return TEXT("");
}


ADialogueActor* UDialogueBlueprintLibrary::GetCurrentDialogueActor(UObject* WorldContextObject)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (!World) return nullptr;
	for (TActorIterator<ADialogueActor> It(World); It; ++It)
	{
		return *It;
	}
	return nullptr;
}

bool UDialogueBlueprintLibrary::NotEqual_Branch(FString A, FString B)
{
	return A == B;
}


