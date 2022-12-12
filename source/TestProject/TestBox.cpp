#include "TestBox.h"

void TestBox::InitData()
{
	vertex_shader_name_ = L"../../data/shader/3DVertexShader.hlsl";
	pixel_shader_name_ = L"../../data/shader/3DPixelShader.hlsl";
	vertex_function_name_ = "VS";
	pixel_function_name = "PS";
	texture_name_ = L"";

	scale_ = { 10.0f, 10.0f, 10.0f };
	location_ = { 0.0f, 0.0f, 0.0f };
	yaw_ = 0.0f;
	pitch_ = 0.0f;
	roll_ = 0.0f;
}

void TestBox::SetVertexData()
{
	vertex_list_.resize(24);
	vertex_list_[0] = Vertex(TVector3(-1.0f, 1.0f, -1.0f), TVector4(1.0f, 0.0f, 0.0f, 1.0f), TVector2(0.0f, 0.0f));
	vertex_list_[1] = Vertex(TVector3(1.0f, 1.0f, -1.0f), TVector4(1.0f, 0.0f, 0.0f, 1.0f), TVector2(1.0f, 0.0f));
	vertex_list_[2] = Vertex(TVector3(1.0f, -1.0f, -1.0f), TVector4(1.0f, 0.0f, 0.0f, 1.0f), TVector2(1.0f, 1.0f));
	vertex_list_[3] = Vertex(TVector3(-1.0f, -1.0f, -1.0f), TVector4(1.0f, 0.0f, 0.0f, 1.0f), TVector2(0.0f, 1.0f));

	vertex_list_[4] = Vertex(TVector3(1.0f, 1.0f, 1.0f), TVector4(0.0f, 0.0f, 0.0f, 1.0f), TVector2(0.0f, 0.0f));
	vertex_list_[5] = Vertex(TVector3(-1.0f, 1.0f, 1.0f), TVector4(0.0f, 1.0f, 0.0f, 1.0f), TVector2(1.0f, 0.0f));
	vertex_list_[6] = Vertex(TVector3(-1.0f, -1.0f, 1.0f), TVector4(0.0f, 1.0f, 0.0f, 1.0f), TVector2(1.0f, 1.0f));
	vertex_list_[7] = Vertex(TVector3(1.0f, -1.0f, 1.0f), TVector4(0.0f, 1.0f, 0.0f, 1.0f), TVector2(0.0f, 1.0f));

	vertex_list_[8] = Vertex(TVector3(1.0f, 1.0f, -1.0f), TVector4(0.0f, 0.0f, 1.0f, 1.0f), TVector2(0.0f, 0.0f));
	vertex_list_[9] = Vertex(TVector3(1.0f, 1.0f, 1.0f), TVector4(0.0f, 0.0f, 1.0f, 1.0f), TVector2(1.0f, 0.0f));
	vertex_list_[10] = Vertex(TVector3(1.0f, -1.0f, 1.0f), TVector4(0.0f, 0.0f, 1.0f, 1.0f), TVector2(1.0f, 1.0f));
	vertex_list_[11] = Vertex(TVector3(1.0f, -1.0f, -1.0f), TVector4(0.0f, 0.0f, 1.0f, 1.0f), TVector2(0.0f, 1.0f));

	vertex_list_[12] = Vertex(TVector3(-1.0f, 1.0f, 1.0f), TVector4(1.0f, 1.0f, 0.0f, 1.0f), TVector2(0.0f, 0.0f));
	vertex_list_[13] = Vertex(TVector3(-1.0f, 1.0f, -1.0f), TVector4(1.0f, 1.0f, 0.0f, 1.0f), TVector2(1.0f, 0.0f));
	vertex_list_[14] = Vertex(TVector3(-1.0f, -1.0f, -1.0f), TVector4(1.0f, 1.0f, 0.0f, 1.0f), TVector2(1.0f, 1.0f));
	vertex_list_[15] = Vertex(TVector3(-1.0f, -1.0f, 1.0f), TVector4(1.0f, 1.0f, 0.0f, 1.0f), TVector2(0.0f, 1.0f));

	vertex_list_[16] = Vertex(TVector3(-1.0f, 1.0f, 1.0f), TVector4(1.0f, 0.5f, 1.0f, 1.0f), TVector2(0.0f, 0.0f));
	vertex_list_[17] = Vertex(TVector3(1.0f, 1.0f, 1.0f), TVector4(1.0f, 0.5f, 1.0f, 1.0f), TVector2(1.0f, 0.0f));
	vertex_list_[18] = Vertex(TVector3(1.0f, 1.0f, -1.0f), TVector4(1.0f, 0.5f, 1.0f, 1.0f), TVector2(1.0f, 1.0f));
	vertex_list_[19] = Vertex(TVector3(-1.0f, 1.0f, -1.0f), TVector4(1.0f, 0.5f, 1.0f, 1.0f), TVector2(0.0f, 1.0f));

	vertex_list_[20] = Vertex(TVector3(-1.0f, -1.0f, -1.0f), TVector4(0.0f, 1.0f, 1.0f, 1.0f), TVector2(0.0f, 0.0f));
	vertex_list_[21] = Vertex(TVector3(1.0f, -1.0f, -1.0f), TVector4(0.0f, 1.0f, 1.0f, 1.0f), TVector2(1.0f, 0.0f));
	vertex_list_[22] = Vertex(TVector3(1.0f, -1.0f, 1.0f), TVector4(0.0f, 1.0f, 1.0f, 1.0f), TVector2(1.0f, 1.0f));
	vertex_list_[23] = Vertex(TVector3(-1.0f, -1.0f, 1.0f), TVector4(0.0f, 1.0f, 1.0f, 1.0f), TVector2(0.0f, 1.0f));
}

void TestBox::SetIndexData()
{
	index_list_.resize(36);
	int index = 0;
	index_list_[index++] = 0; 	index_list_[index++] = 1; 	index_list_[index++] = 2; 	index_list_[index++] = 0;	index_list_[index++] = 2; 	index_list_[index++] = 3;
	index_list_[index++] = 4; 	index_list_[index++] = 5; 	index_list_[index++] = 6; 	index_list_[index++] = 4;	index_list_[index++] = 6; 	index_list_[index++] = 7;
	index_list_[index++] = 8; 	index_list_[index++] = 9; 	index_list_[index++] = 10; index_list_[index++] = 8;	index_list_[index++] = 10; index_list_[index++] = 11;
	index_list_[index++] = 12; index_list_[index++] = 13; index_list_[index++] = 14; index_list_[index++] = 12;	index_list_[index++] = 14; index_list_[index++] = 15;
	index_list_[index++] = 16; index_list_[index++] = 17; index_list_[index++] = 18; index_list_[index++] = 16;	index_list_[index++] = 18; index_list_[index++] = 19;
	index_list_[index++] = 20; index_list_[index++] = 21; index_list_[index++] = 22; index_list_[index++] = 20;	index_list_[index++] = 22; index_list_[index++] = 23;
}
