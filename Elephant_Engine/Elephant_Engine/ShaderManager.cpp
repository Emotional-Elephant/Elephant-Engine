#include "ShaderManager.h"

ComPtr<ID3D11VertexShader> ShaderManager::GetVertexShader(std::wstring file_name, std::string func_name)
{
    HRESULT hr;
    ID3DBlob* pErrorCode = nullptr;

    auto iter = vs_list_.find(file_name);
    if (iter != vs_list_.end())
    {
        return iter->second.second;
    }

    DWORD shader_flags = D3DCOMPILE_SKIP_OPTIMIZATION;
#if defined( _DEBUG ) 
    shader_flags |= D3DCOMPILE_DEBUG;
#endif
    ID3DBlob* vs_code_ptr = nullptr;
    hr = D3DCompileFromFile(
        file_name.c_str(),
        NULL,
        NULL,
        func_name.c_str(),
        "vs_5_0",
        shader_flags,
        0,
        &vs_code_ptr,
        &pErrorCode);
    if (FAILED(hr))
    {
        if (pErrorCode)
        {
            OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
            pErrorCode->Release();
        }
        assert(SUCCEEDED(hr));
    }

    ID3D11VertexShader* vertex_shader_ptr = nullptr;
    hr = Device::GetInstance().GetDevice()->CreateVertexShader(
        vs_code_ptr->GetBufferPointer(),
        vs_code_ptr->GetBufferSize(),
        NULL,
        &vertex_shader_ptr);
    assert(SUCCEEDED(hr));

    ComPtr<ID3D11VertexShader> vertex_shader_comptr = ComPtr<ID3D11VertexShader>(vertex_shader_ptr);
    if (vertex_shader_ptr)
    {
        vs_list_.insert(
            {
                file_name,
                {
                    ComPtr<ID3DBlob>(vs_code_ptr),
                    vertex_shader_comptr
                }
            }
        );
    }

    return vertex_shader_comptr;
}

ComPtr<ID3DBlob> ShaderManager::GetVSCode(std::wstring file_name, std::string func_name)
{
    HRESULT hr;
    ID3DBlob* pErrorCode = nullptr;

    auto iter = vs_list_.find(file_name);
    if (iter != vs_list_.end())
    {
        return (iter->second).first;
    }

    DWORD shader_flags = D3DCOMPILE_SKIP_OPTIMIZATION;
#if defined( _DEBUG ) 
    shader_flags |= D3DCOMPILE_DEBUG;
#endif
    ID3DBlob* vs_code_ptr = nullptr;
    hr = D3DCompileFromFile(
        file_name.c_str(),
        NULL,
        NULL,
        func_name.c_str(),
        "vs_5_0",
        shader_flags,
        0,
        &vs_code_ptr,
        &pErrorCode);
    if (FAILED(hr))
    {
        if (pErrorCode)
        {
            OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
            pErrorCode->Release();
        }
        assert(SUCCEEDED(hr));
    }

    ID3D11VertexShader* vertex_shader_ptr = nullptr;
    hr = Device::GetInstance().GetDevice()->CreateVertexShader(
        vs_code_ptr->GetBufferPointer(),
        vs_code_ptr->GetBufferSize(),
        NULL,
        &vertex_shader_ptr);
    assert(SUCCEEDED(hr));

    ComPtr<ID3DBlob> vs_code_comptr = ComPtr<ID3DBlob>(vs_code_ptr);
    if (vertex_shader_ptr)
    {
        vs_list_.insert(
            {
                file_name,
                {
                    vs_code_comptr,
                    ComPtr<ID3D11VertexShader>(vertex_shader_ptr)
                }
            }
        );
    }

    return vs_code_comptr;
}

ComPtr<ID3D11PixelShader> ShaderManager::GetPixelShader(std::wstring file_name, std::string func_name)
{
    HRESULT hr;
    ID3DBlob* pErrorCode = nullptr;

    auto iter = ps_list_.find(file_name);
    if (iter != ps_list_.end())
    {
        return iter->second;
    }

    DWORD shader_flags = D3DCOMPILE_SKIP_OPTIMIZATION;
#if defined( _DEBUG ) 
    shader_flags |= D3DCOMPILE_DEBUG;
#endif
    ID3DBlob* ps_code_ptr = nullptr;
    hr = D3DCompileFromFile(
        file_name.c_str(),
        NULL,
        NULL,
        func_name.c_str(),
        "ps_5_0",
        shader_flags,
        0,
        &ps_code_ptr,
        &pErrorCode);
    if (FAILED(hr))
    {
        if (pErrorCode)
        {
            OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
            pErrorCode->Release();
        }
        assert(SUCCEEDED(hr));
    }

    ID3D11PixelShader* pixel_shader_ptr = nullptr;
    hr = Device::GetInstance().GetDevice()->CreatePixelShader(
        ps_code_ptr->GetBufferPointer(),
        ps_code_ptr->GetBufferSize(),
        NULL,
        &pixel_shader_ptr);
    assert(SUCCEEDED(hr));

    ComPtr<ID3D11PixelShader> pixel_shader_comptr = ComPtr<ID3D11PixelShader>(pixel_shader_ptr);
    if (pixel_shader_ptr)
    {
        ps_list_.insert(
            {
                file_name,
                ComPtr<ID3D11PixelShader>(pixel_shader_ptr)
            }
        );
    }

    return pixel_shader_comptr;
}

bool ShaderManager::Release()
{
    vs_list_.clear();
    ps_list_.clear();
	return false;
}
