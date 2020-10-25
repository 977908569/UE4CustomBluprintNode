#pragma once
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DialogueActor.h"
#include "LatentActions.h"
#include "Engine/LatentActionManager.h"
#include "Engine.h"
#include "DialogueBlueprintLibrary.generated.h"

UCLASS(BlueprintType)
class DIALOGUEBLUEPRINTNODE_API UDialogueBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, meta = (Latent, LatentInfo = "LatentInfo", WorldContext = "WorldContextObject", BlueprintInternalUseOnly = "true"), Category = "Dialogue")
		static void WaitInput(UObject* WorldContextObject, FLatentActionInfo LatentInfo);

	UFUNCTION(BlueprintCallable, meta = (Latent, LatentInfo = "LatentInfo", WorldContext = "WorldContextObject", BlueprintInternalUseOnly = "true"), Category = "Dialogue")
		static FString WaitSelect(UObject* WorldContextObject, FLatentActionInfo LatentInfo);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
		static ADialogueActor* GetCurrentDialogueActor(UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = PinOptions, meta = (BlueprintInternalUseOnly = "TRUE"))
		static bool NotEqual_Branch(FString A, FString B);
};
