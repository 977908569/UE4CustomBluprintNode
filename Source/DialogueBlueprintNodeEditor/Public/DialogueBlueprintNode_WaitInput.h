#pragma once
#include "K2Node.h"
#include "KismetCompiler.h"
#include "DialogueBlueprintNode_WaitInput.generated.h"
UCLASS()
class DIALOGUEBLUEPRINTNODEEDITOR_API UDialogueBlueprintNode_WaitInput : public UK2Node
{
	GENERATED_BODY()
public:
	void AllocateDefaultPins() override;
	FText GetTooltipText() const override;
	FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	FText GetMenuCategory() const override;
	bool IsNodePure() const override { return false; }

	void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
	virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;

	UEdGraphPin* GetThenPin() const;
};
