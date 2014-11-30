#include "bytecodegenerator.h"

namespace mathvm
{

const TokenKind TypeInferencer::assignOps[]  = {tASSIGN, tINCRSET, tDECRSET};
const TokenKind TypeInferencer::compareOps[] = {tEQ, tNEQ, tNOT, tLT, tLE, tGT, tGE, tOR, tAND};
const TokenKind TypeInferencer::bitOps[]     = {tAOR, tAAND, tAXOR};
const TokenKind TypeInferencer::ariphmOps[]  = {tADD, tSUB, tMUL, tDIV};

TypeInferencer::TypeInferencer() {
}

TypeInferencer::~TypeInferencer() {
}

//VarType TypeInferencer::resolveType(AstNode *node) {
//    node->visit(this);
//    return _type;
//}

bool TypeInferencer::find(TokenKind op, const TokenKind ops[], int count) {
    for (int i = 0; i < count; ++i) {
        if (ops[i] == op) {
            return true;
        }
    }
    return false;
}

VarType TypeInferencer::commonTypeForBinOp(TokenKind binOp, VarType left, VarType right) const
{
    //  =  +=  -=
    if (find(binOp, assignOps, ASSIGN_COUNT)) {
        return left;
    }

    //  ==  !=  !  >  >=  <  <=  ||  &&
    else if (find(binOp, compareOps, COMPARE_COUNT)) {
        return commonType(left, right);
    }

    //  |  &  ^
    else if (find(binOp, bitOps, BIT_COUNT)) {
        return VT_INT;
    }

    //  +  -  *  /
    else if (find(binOp, ariphmOps, ARIPHM_COUNT)) {
        return commonType(left, right);
    }

    //  %
    else if (binOp == tMOD) {
        return VT_INT;
    }
}

VarType TypeInferencer::commonType(const VarType v1, const VarType v2) const
{
    if (v1 == VT_DOUBLE || v2 == VT_DOUBLE) {
        return VT_DOUBLE;
    }
    else if (v1 == VT_INT || v2 == VT_INT) {
        return VT_INT;
    }

    return VT_STRING;
}

void TypeInferencer::setScope(Scope *scope)
{
    _scope = scope;
}

VarType TypeInferencer::inferredType() const {
    return _type;
}

void TypeInferencer::visitUnaryOpNode(UnaryOpNode *node) {
    node->operand()->visit(this);
}

/*
 * logic operator ??
*/
void TypeInferencer::visitBinaryOpNode(BinaryOpNode *node) {
    node->left()->visit(this);
    VarType leftType = inferredType();
    node->right()->visit(this);
    VarType rightType = inferredType();

    _type = commonType(leftType, rightType);

    switch(node->kind()) {
    case tADD:
        break;
    case tSUB:
        break;
    case tMUL:
        break;
    case tDIV:
        break;
    }
}

void TypeInferencer::visitIntLiteralNode(IntLiteralNode *node) {
    _type = VT_INT;
}

void TypeInferencer::visitDoubleLiteralNode(DoubleLiteralNode *node) {
    _type = VT_DOUBLE;
}

void TypeInferencer::visitStringLiteralNode(StringLiteralNode *node) {
    _type = VT_STRING;
}

void TypeInferencer::visitStoreNode(StoreNode *node) {
    //unnecessary
}

void TypeInferencer::visitLoadNode(LoadNode *node) {
    _type = node->var()->type();
}

void TypeInferencer::visitBlockNode(BlockNode *node) {
    //unnecessary
}

void TypeInferencer::visitIfNode(IfNode *node) {
    //unnecessary
}

void TypeInferencer::visitWhileNode(WhileNode *node) {
    //unnecessary
}

void TypeInferencer::visitForNode(ForNode *node) {
    //unnecessary
}

void TypeInferencer::visitFunctionNode(FunctionNode *node) {
    //unnecessary
}

void TypeInferencer::visitCallNode(CallNode *node) {
    _type = _scope->lookupFunction(node->name())->returnType();
}

void TypeInferencer::visitReturnNode(ReturnNode *node) {
    //unnecessary
}

void TypeInferencer::visitPrintNode(PrintNode *node) {
    //unnecessary
}

void TypeInferencer::visitNativeCallNode(NativeCallNode *node) {
    SignatureElement returnElement = node->nativeSignature().at(0);
    _type = returnElement.first;
}


}
