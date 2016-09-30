// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	C++ class header boilerplate exported from UnrealHeaderTool.
	This is automatically generated by the tools.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectBase.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef EXTENDEDLIBRARY_XLCharacterResources_generated_h
#error "XLCharacterResources.generated.h already included, missing '#pragma once' in XLCharacterResources.h"
#endif
#define EXTENDEDLIBRARY_XLCharacterResources_generated_h

#define UE4ExtendedLibrary_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Data_XLCharacterResources_h_10_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execRegenerateShield) \
	{ \
		P_GET_PROPERTY(UFloatProperty,Z_Param_DeltaTime); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->RegenerateShield(Z_Param_DeltaTime); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execRegenerateEnergy) \
	{ \
		P_GET_PROPERTY(UFloatProperty,Z_Param_DeltaTime); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->RegenerateEnergy(Z_Param_DeltaTime); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execRegenerateStamina) \
	{ \
		P_GET_PROPERTY(UFloatProperty,Z_Param_DeltaTime); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->RegenerateStamina(Z_Param_DeltaTime); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execRegenerateHealth) \
	{ \
		P_GET_PROPERTY(UFloatProperty,Z_Param_DeltaTime); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->RegenerateHealth(Z_Param_DeltaTime); \
		P_NATIVE_END; \
	}


#define UE4ExtendedLibrary_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Data_XLCharacterResources_h_10_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execRegenerateShield) \
	{ \
		P_GET_PROPERTY(UFloatProperty,Z_Param_DeltaTime); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->RegenerateShield(Z_Param_DeltaTime); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execRegenerateEnergy) \
	{ \
		P_GET_PROPERTY(UFloatProperty,Z_Param_DeltaTime); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->RegenerateEnergy(Z_Param_DeltaTime); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execRegenerateStamina) \
	{ \
		P_GET_PROPERTY(UFloatProperty,Z_Param_DeltaTime); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->RegenerateStamina(Z_Param_DeltaTime); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execRegenerateHealth) \
	{ \
		P_GET_PROPERTY(UFloatProperty,Z_Param_DeltaTime); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->RegenerateHealth(Z_Param_DeltaTime); \
		P_NATIVE_END; \
	}


#define UE4ExtendedLibrary_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Data_XLCharacterResources_h_10_INCLASS_NO_PURE_DECLS \
	private: \
	static void StaticRegisterNativesUXLCharacterResources(); \
	friend EXTENDEDLIBRARY_API class UClass* Z_Construct_UClass_UXLCharacterResources(); \
	public: \
	DECLARE_CLASS(UXLCharacterResources, UActorComponent, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/ExtendedLibrary"), NO_API) \
	DECLARE_SERIALIZER(UXLCharacterResources) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define UE4ExtendedLibrary_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Data_XLCharacterResources_h_10_INCLASS \
	private: \
	static void StaticRegisterNativesUXLCharacterResources(); \
	friend EXTENDEDLIBRARY_API class UClass* Z_Construct_UClass_UXLCharacterResources(); \
	public: \
	DECLARE_CLASS(UXLCharacterResources, UActorComponent, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/ExtendedLibrary"), NO_API) \
	DECLARE_SERIALIZER(UXLCharacterResources) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define UE4ExtendedLibrary_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Data_XLCharacterResources_h_10_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UXLCharacterResources(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UXLCharacterResources) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UXLCharacterResources); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UXLCharacterResources); \
private: \
	/** Private copy-constructor, should never be used */ \
	NO_API UXLCharacterResources(const UXLCharacterResources& InCopy); \
public:


#define UE4ExtendedLibrary_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Data_XLCharacterResources_h_10_ENHANCED_CONSTRUCTORS \
private: \
	/** Private copy-constructor, should never be used */ \
	NO_API UXLCharacterResources(const UXLCharacterResources& InCopy); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UXLCharacterResources); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UXLCharacterResources); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UXLCharacterResources)


#define UE4ExtendedLibrary_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Data_XLCharacterResources_h_7_PROLOG
#define UE4ExtendedLibrary_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Data_XLCharacterResources_h_10_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	UE4ExtendedLibrary_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Data_XLCharacterResources_h_10_RPC_WRAPPERS \
	UE4ExtendedLibrary_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Data_XLCharacterResources_h_10_INCLASS \
	UE4ExtendedLibrary_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Data_XLCharacterResources_h_10_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define UE4ExtendedLibrary_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Data_XLCharacterResources_h_10_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	UE4ExtendedLibrary_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Data_XLCharacterResources_h_10_RPC_WRAPPERS_NO_PURE_DECLS \
	UE4ExtendedLibrary_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Data_XLCharacterResources_h_10_INCLASS_NO_PURE_DECLS \
	UE4ExtendedLibrary_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Data_XLCharacterResources_h_10_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID UE4ExtendedLibrary_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Data_XLCharacterResources_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
