#include "ShaderManager.h"

HRESULT ShaderManager::GetVertexShader(std::weak_ptr<ID3D11VertexShader*>& vertex_shader, std::wstring file_name, std::string func_name)
{
    HRESULT hr;
    ID3DBlob* pErrorCode = nullptr;

    auto iter = vs_list_.find(file_name);
    if (iter != vs_list_.end())
    {
        vertex_shader = std::weak_ptr<ID3D11VertexShader*>((iter->second).second);
        return S_OK;
    }

    ID3DBlob* vs_code_ptr = nullptr;
    hr = D3DCompileFromFile(
        file_name.c_str(),
        NULL,
        NULL,
        func_name.c_str(),
        "vs_5_0",
        0,
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
        return hr;
    }
    
    ID3D11VertexShader* vertex_shader_ptr;
    hr = I_Device.GetDevice()->CreateVertexShader(
        vs_code_ptr->GetBufferPointer(),
        vs_code_ptr->GetBufferSize(),
        NULL,
        &vertex_shader_ptr);
    if (FAILED(hr))
        return hr;

    if (vertex_shader_ptr)
    {
        if (SUCCEEDED(hr))
        {
            vs_list_.insert(
                { 
                    file_name, 
                    {   
                        std::make_shared<ID3DBlob*>(vs_code_ptr), 
                        std::make_shared<ID3D11VertexShader*>(vertex_shader_ptr)
                    } 
                }
            );
        }
    }

    return hr;
}

HRESULT ShaderManager::GetVSCode(std::weak_ptr<ID3DBlob*>& vs_code, std::wstring file_name, std::string func_name)
{
    HRESULT hr;
    ID3DBlob* pErrorCode = nullptr;

    auto iter = vs_list_.find(file_name);
    if (iter != vs_list_.end())
    {
        vs_code = std::weak_ptr<ID3DBlob*>((iter->second).first);
        return S_OK;
    }

    ID3DBlob* vs_code_ptr = nullptr;
    hr = D3DCompileFromFile(
        file_name.c_str(),
        NULL,
        NULL,
        func_name.c_str(),
        "vs_5_0",
        0,
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
        return hr;
    }

    ID3D11VertexShader* vertex_shader_ptr;
    hr = I_Device.GetDevice()->CreateVertexShader(
        vs_code_ptr->GetBufferPointer(),
        vs_code_ptr->GetBufferSize(),
        NULL,
        &vertex_shader_ptr);
    if (FAILED(hr))
        return hr;

    if (vertex_shader_ptr)
    {
        if (SUCCEEDED(hr))
        {
            vs_list_.insert(
                {
                    file_name,
                    {
                        std::make_shared<ID3DBlob*>(vs_code_ptr),
                        std::make_shared<ID3D11VertexShader*>(vertex_shader_ptr)
                    }
                }
            );
        }
    }

    return hr;
}

HRESULT ShaderManager::GetPixelShader(std::weak_ptr<ID3D11PixelShader*>& pixel_shader, std::wstring file_name, std::string func_name)
{
    HRESULT hr;
    ID3DBlob* pErrorCode = nullptr;

    auto iter = ps_list_.find(file_name);
    if (iter != ps_list_.end())
    {
        pixel_shader = std::weak_ptr<ID3D11PixelShader*>(iter->second);
        return S_OK;
    }

    ID3DBlob* ps_code_ptr = nullptr;
    hr = D3DCompileFromFile(
        file_name.c_str(),
        NULL,
        NULL,
        func_name.c_str(),
        "vs_5_0",
        0,
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
        return hr;
    }

    ID3D11PixelShader* pixel_shader_ptr;
    hr = I_Device.GetDevice()->CreatePixelShader(
        ps_code_ptr->GetBufferPointer(),
        ps_code_ptr->GetBufferSize(),
        NULL,
        &pixel_shader_ptr);
    if (FAILED(hr))
        return hr;

    if (pixel_shader_ptr)
    {
        if (SUCCEEDED(hr))
        {
            ps_list_.insert(
                {
                    file_name,
                    std::make_shared<ID3D11PixelShader*>(pixel_shader_ptr)
                }
            );
        }
    }

    return hr;
}

bool ShaderManager::Release()
{
    vs_list_.clear();
    ps_list_.clear();
	return false;
}
