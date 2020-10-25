#include "DialogueBlueprintNode_WaitInput.h"
#include "EdGraphSchema_K2.h"
#include "BlueprintNodeSpawner.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "KismetCompiler.h"
#include "K2Node_CallFunction.h"
#include "DialogueBlueprintLibrary.h"

void UDialogueBlueprintNode_WaitInput::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);
}

FText UDialogueBlueprintNode_WaitInput::GetTooltipText() const
{
	return  FText::FromString(TEXT("Wait Input..."));
}

FText UDialogueBlueprintNode_WaitInput::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString(TEXT("Wait Input"));
}

FText UDialogueBlueprintNode_WaitInput::GetMenuCategory() const
{
	return FText::FromString(TEXT("Dialogue"));
}

void UDialogueBlueprintNode_WaitInput::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	UClass* ActionKey = GetClass();

	if (ActionRegistrar.IsOpenForRegistration(ActionKey))
	{
		UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
		check(NodeSpawner != nullptr);

		ActionRegistrar.AddBlueprintAction(ActionKey, NodeSpawner);
	}
}

void UDialogueBlueprintNode_WaitInput::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	Super::ExpandNode(CompilerContext, SourceGraph);
	UEdGraphPin* ExecPin = GetExecPin();
	UEdGraphPin* ThenPin = GetThenPin();

	UK2Node_CallFunction* CallFuncNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
	CallFuncNode->FunctionReference.SetExternalMember(GET_FUNCTION_NAME_CHECKED(UDialogueBlueprintLibrary, WaitInput), UDialogueBlueprintLibrary::StaticClass());
	CallFuncNode->AllocateDefaultPins();

	if (ExecPin && ThenPin)
	{
		CompilerContext.MovePinLinksToIntermediate(*ExecPin, *(CallFuncNode->GetExecPin()));
		CompilerContext.MovePinLinksToIntermediate(*ThenPin, *(CallFuncNode->GetThenPin()));
	}
	BreakAllNodeLinks();
}

UEdGraphPin* UDialogueBlueprintNode_WaitInput::GetThenPin() const
{
	UEdGraphPin* Pin = FindPin(UEdGraphSchema_K2::PN_Then);
	check(Pin == nullptr || Pin->Direction == EGPD_Output); // If pin exists, it must be output
	return Pin;
}
