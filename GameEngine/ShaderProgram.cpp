#include "ShaderProgram.h"

#include <codecvt>
#include <wrl/client.h>
#include <d3dcompiler.h>

HRESULT ShaderProgram::CompileShader(const char * const pTarget, ID3DBlob** const pShaderBlob)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
	
	const DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;
	const auto result = D3DCompileFromFile(converter.from_bytes(mFilename).c_str(), nullptr, nullptr, "main", pTarget,
		shaderFlags, 0, pShaderBlob, &errorBlob);

	if (FAILED(result))
	{
		if (errorBlob)
		{
			OutputDebugStringA(reinterpret_cast<const char*>(errorBlob->GetBufferPointer()));
		}
	}

	return result;
}