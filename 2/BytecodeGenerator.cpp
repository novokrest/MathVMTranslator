#include "BytecodeGenerator.h"

namespace mathvm {

BytecodeGenerator::BytecodeGenerator() {
}

BytecodeGenerator::~BytecodeGenerator() {
}

void BytecodeGenerator::visitUnaryOpNode(UnaryOpNode *node) {
    AstNode* operand = node->operand();
    operand->visit(this);
    operand->visit(_typeInferencer);
    VarType operandType = _typeInferencer.inferredType();

    TokenKind operation = node->kind();
    switch(operation) {
    case tADD:
        break;
    case tSUB:
        if (operandType == VT_DOUBLE) {
            _bytecode.add(BC_DNEG);
        }
        else if (operandType == VT_INT) {
            _bytecode.add(BC_INEG);
        }
        else {
            assert(false);
        }
        break;
    default:
        break;
    }
}

void BytecodeGenerator::visitBinaryOpNode(BinaryOpNode *node)
{
    AstNode* leftOperand = node->left();
    AstNode* rightOperand = node->right();
    leftOperand->visit(this);
    rightOperand->visit(this);

    leftOperand->visit(_typeInferencer);
    VarType leftType = _typeInferencer.inferredType();
    rightOperand->visit(_typeInferencer);
    VarType rightType = _typeInferencer.inferredType();
    
    VarType result = _typeInferencer.resolveType(leftType, rightType);
}

void BytecodeGenerator::visitIntLiteralNode(IntLiteralNode *node)
{}

void BytecodeGenerator::visitDoubleLiteralNode(DoubleLiteralNode *node)
{}

void BytecodeGenerator::visitStringLiteralNode(StringLiteralNode *node)
{}

void BytecodeGenerator::visitStoreNode(StoreNode *node)
{}

void BytecodeGenerator::visitLoadNode(LoadNode *node)
{}

void BytecodeGenerator::visitBlockNode(BlockNode *node)
{}

void BytecodeGenerator::visitIfNode(IfNode *node)
{}

void BytecodeGenerator::visitWhileNode(WhileNode *node)
{}

void BytecodeGenerator::visitForNode(ForNode *node)
{}

void BytecodeGenerator::visitFunctionNode(FunctionNode *node)
{}

void BytecodeGenerator::visitCallNode(CallNode *node)
{}

void BytecodeGenerator::visitReturnNode(ReturnNode *node)
{}

void BytecodeGenerator::visitPrintNode(PrintNode *node)
{}

void BytecodeGenerator::visitNativeCallNode(NativeCallNode *node)
{}

}
