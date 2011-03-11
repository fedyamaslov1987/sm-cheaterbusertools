
#if defined _memoryhack_included
  #endinput
#endif
#define _memoryhack_included


enum MemHackLibrary
{
	MemHackLibrary_Server,	/**< server.dll/server_i486.so */
	MemHackLibrary_Engine,	/**< engine.dll/engine_*.so */
};

enum MemHackType
{
	MEM_TYPE_CODE,			// Code (.text segment, mprotect or VirtualProtect)
	//MEM_TYPE_DATA,			// Data (.data segment, writable by default) Disable now
	MEM_TYPE_RODATA,		// Read Only Data (.rodata on Linux, .rdata on Windows)
};



/**
 * Create Memoey Hack Handle from user input
 *
 * @param lib			MemHackLibrary Type.
 * @param signature		Binary data to search for in the library.  If it starts with '@',
 *						the bytes parameter is ignored and the signature is interpreted
 *						as a symbol lookup in the library.
 * @param bytes			Number of bytes in the binary search string.
 * @param offset		Offset value.
 * @param memType		MemHackType, Default = MEM_TYPE_CODE
 * @return				A Memory Hack or INVALID_HANDLE in failure.
 */

native Handle:CreateMemHackFromSig(MemHackLibrary:lib, const String:signature[], bytes, offset = 0, MemHackType:memType = MEM_TYPE_CODE);

/**
 * Create Memoey Hack Handle from gameconfig
 *
 * @param gameconf			GameConfig Handle.
 * @param signaturename		Whether to look in Signature.
 * @param offsetname		Whether to look in Offset.
 * @param memType			MemHackType, Default = MEM_TYPE_CODE
 * @return					A Memory Hack or INVALID_HANDLE in failure.
 */
native Handle:CreateMemHackFromConf(Handle:gameconf, const String:signaturename[], const String:offsetname[] = "", MemHackType:memType = MEM_TYPE_CODE);


/**
 * Set MemHackType
 *
 * @param hndl			Memory Hack Handle.
 * @param memType		MemHackType.
 * @noreturn
 * @error				Invalid Handle.
 */
native MH_SetType(Handle:hndl, MemHackType:memType);

/**
 * Add Address Offset
 *
 * @param hndl			Memory Hack Handle.
 * @param offset		Offset to add
 * @noreturn
 * @error				Invalid Handle.
 */
native MH_AddOffSet(Handle:hndl, offset);


/**
 * Read or Patch Memoey Address
 *
 * @param hndl			Memory Hack Handle.
 * @param offset		Offset to add
 * @return  			for MH_Patch_* Only true/false.
 * @noreturn			for MH_Read_* Only.
 * @error				Invalid Handle or size <= 0.
 */
//char
native MH_Read_Bytes(Handle:hndl, buffer[], size);
native bool:MH_Patch_Bytes(Handle:hndl, const value[], size);
native MH_Read_UnsignedBytes(Handle:hndl, buffer[], size);
native bool:MH_Patch_UnsignedBytes(Handle:hndl, const value[], size);

// short
native MH_Read_Words(Handle:hndl, buffer[], size);
native bool:MH_Patch_Words(Handle:hndl, const value[], size);
native MH_Read_UnsignedWords(Handle:hndl, buffer[], size);
native bool:MH_Patch_UnsignedWords(Handle:hndl, const value[], size);

// int
native MH_Read_Dwords(Handle:hndl, buffer[], size);
native bool:MH_Patch_Dwords(Handle:hndl, const value[], size);
native MH_Read_UnsignedDwords(Handle:hndl, buffer[], size);
native bool:MH_Patch_UnsignedDwords(Handle:hndl, const value[], size);

// float
native MH_Read_Floats(Handle:hndl, Float:buffer[], size);
native bool:MH_Patch_Floats(Handle:hndl, const Float:value[], size);

// pointer
native Handle:MH_Read_Pointer(Handle:hndl, MemHackType:memType = MEM_TYPE_CODE);
native bool:MH_Patch_Pointer(Handle:hndl, Handle:patch_hndl);

stock bool:MH_Patch_String(Handle:_hndl, const String:input[], size, bool:endString = false)
{
	if(size <= 0)
		return false;
	
	new realsize = (endString) ? size + 1 : size;
	new bytes[realsize];
	for(new i=0;i<size;i++)
	{
		bytes[i] = input[i];
	}
	if(endString)
	{
		bytes[size] = '\0';
	}
	return MH_Patch_UnsignedBytes(_hndl,bytes,realsize);
}

stock MH_Read_String(Handle:_hndl, String:buffer[], size)
{
	if(size <= 0)
		return;
	
	new temp[size];
	if(MH_Read_UnsignedBytes(_hndl,temp,size))
	{
		for(new i=0;i<size;i++) // any better way to do this?
		{
			buffer[i] = temp[i];
		}
	}
}


/**
 * Read patch values from gamedata
 *
 * @param hndl			Game Config Handle.
 * @param key			Key to retrieve from the offset section.
 * @param buffer		Destination buffer.
 * @param size			Size of the buffer
 * @return  			True if all patch value get sucess, false otherwise.
 */
stock bool:MH_ReadPatchBytes(Handle:gameconf, const String:key[],buffer[], size)
{
	if(size <= 0)
		return false;
	
	decl offset;
	decl String:offsetname[128];
	for(new i=1;i<=size;i++)
	{
		Format(offsetname,sizeof(offsetname),"%s_%d",key,i);
		offset = GameConfGetOffset(gameconf,offsetname);
		if(offset == -1)
			return false;
		buffer[i-1] = offset;
	}
	return true;
}


/**
 * Do not edit below this line!
 */
public Extension:__ext_memoryhack= 
{
	name = "MemoryHack",
	file = "memoryhack.ext",
#if defined AUTOLOAD_EXTENSIONS
	autoload = 1,
#else
	autoload = 0,
#endif
#if defined REQUIRE_EXTENSIONS
	required = 1,
#else
	required = 0,
#endif
};
