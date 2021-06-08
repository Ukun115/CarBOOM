#include "stdafx.h"
#include "SpriteRender.h"


// ���_�\����
struct SimpleVertex
{
    Vector4 pos;    // ���_���W
    Vector2 uv;     // UV���W
};

auto& renderContext = g_graphicsEngine->GetRenderContext();

bool SpriteRender::Start()
{


	//Start�֐���return��
	return true;
}

SpriteRender::~SpriteRender()
{

}

void SpriteRender::Update()
{
    // �X�v���C�g�̃h���[�R�[�������s����
    m_sprite.Draw(renderContext);
}

void SpriteRender::Init(const char* filepath, float width, float height, AlphaBlendMode mode)
{
	m_spriteInitData.m_ddsFilePath[0] = filepath;					//�t�@�C���p�X
	m_spriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";		//�V�F�[�_�[�t�@�C���̃p�X���w��
	m_spriteInitData.m_width = width;								//����
	m_spriteInitData.m_height = height;								//�c��
	m_spriteInitData.m_alphaBlendMode = mode;						//����
	m_spriteInitData.m_alphaBlendMode = AlphaBlendMode_Add;			//���Z�����̐ݒ�ŕ`�悷��

	m_sprite.Init(m_spriteInitData);


}

// ���[�g�V�O�l�`���̏�����
void SpriteRender::InitRootSignature(RootSignature& rs)
{
    rs.Init(D3D12_FILTER_MIN_MAG_MIP_LINEAR,
        D3D12_TEXTURE_ADDRESS_MODE_WRAP,
        D3D12_TEXTURE_ADDRESS_MODE_WRAP,
        D3D12_TEXTURE_ADDRESS_MODE_WRAP);
}

// �p�C�v���C���X�e�[�g�̏�����
void SpriteRender::InitPipelineState(PipelineState& pipelineState, RootSignature& rs, Shader& vs, Shader& ps)
{
    // ���_���C�A�E�g���`����
    D3D12_INPUT_ELEMENT_DESC inputElementDescs[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 16, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
    };

    // �p�C�v���C���X�e�[�g���쐬
    D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = { 0 };
    psoDesc.InputLayout = { inputElementDescs, _countof(inputElementDescs) };
    psoDesc.pRootSignature = rs.Get();
    psoDesc.VS = CD3DX12_SHADER_BYTECODE(vs.GetCompiledBlob());
    psoDesc.PS = CD3DX12_SHADER_BYTECODE(ps.GetCompiledBlob());
    psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
    psoDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
    psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
    psoDesc.DepthStencilState.DepthEnable = FALSE;
    psoDesc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ZERO;
    psoDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
    psoDesc.DepthStencilState.StencilEnable = FALSE;
    psoDesc.SampleMask = UINT_MAX;
    psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    psoDesc.NumRenderTargets = 1;
    psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
    psoDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;
    psoDesc.SampleDesc.Count = 1;
    psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
    pipelineState.Init(psoDesc);
}
