#pragma once
#include "GameFramework/Actor.h"
#include "DialogueActor.generated.h"
UCLASS(BlueprintType)
class DIALOGUEBLUEPRINTNODE_API ADialogueActor : public AActor
{
	GENERATED_BODY()
public:
	ADialogueActor();

	UPROPERTY(BlueprintReadWrite)
	bool bInput = false;
};