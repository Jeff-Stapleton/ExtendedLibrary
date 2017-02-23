// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	C++ class header boilerplate exported from UnrealHeaderTool.
	This is automatically generated by the tools.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef EXTENDEDLIBRARY_XLAbilityManager_generated_h
#error "XLAbilityManager.generated.h already included, missing '#pragma once' in XLAbilityManager.h"
#endif
#define EXTENDEDLIBRARY_XLAbilityManager_generated_h

#define UE4ExtendedLibrary_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Managers_XLAbilityManager_h_9_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execDeactivateAbility) \
	{ \
		P_GET_PROPERTY(UIntProperty,Z_Param_Ability); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->DeactivateAbility(Z_Param_Ability); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execActivateAbility) \
	{ \
		P_GET_PROPERTY(UIntProperty,Z_Param_Ability); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->ActivateAbility(Z_Param_Ability); \
		P_NATIVE_END; \
	}


#define UE4ExtendedLibrary_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Managers_XLAbilityManager_h_9_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execDeactivateAbility) \
	{ \
		P_GET_PROPERTY(UIntProperty,Z_Param_Ability); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->DeactivateAbility(Z_Param_Ability); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execActivateAbility) \
	{ \
		P_GET_PROPERTY(UIntProperty,Z_Param_Ability); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->ActivateAbility(Z_Param_Ability); \
		P_NATIVE_END; \
	}


#define UE4ExtendedLibrary_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Managers_XLAbilityManager_h_9_INCLASS_NO_PURE_DECLS \
	private: \
	static void StaticRegisterNativesUXLAbilityManager(); \
	friend EXTENDEDLIBRARY_API class UClass* Z_Construct_UClass_UXLAbilityManager(); \
	public: \
	DECLARE_CLASS(UXLAbilityManager, UActorComponent, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/ExtendedLibrary"), NO_API) \
	DECLARE_SERIALIZER(UXLAbilityManager) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define UE4ExtendedLibrary_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Managers_XLAbilityManager_h_9_INCLASS \
	private: \
	static void StaticRegisterNativesUXLAbilityManager(); \
	friend EXTENDEDLIBRARY_API class UClass* Z_Construct_UClass_UXLAbilityManager(); \
	public: \
	DECLARE_CLASS(UXLAbilityManager, UActorComponent, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/ExtendedLibrary"), NO_API) \
	DECLARE_SERIALIZER(UXLAbilityManager) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define UE4ExtendedLibrary_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Managers_XLAbilityManager_h_9_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UXLAbilityManager(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UXLAbilityManager) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UXLAbilityManager); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UXLAbilityManager); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UXLAbilityManager(UXLAbilityManager&&); \
	NO_API UXLAbilityManager(const UXLAbilityManager&); \
public:


#define UE4ExtendedLibrary_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Managers_XLAbilityManager_h_9_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UXLAbilityManager(UXLAbilityManager&&); \
	NO_API UXLAbilityManager(const UXLAbilityManager&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UXLAbilityManager); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UXLAbilityManager); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UXLAbilityManager)


#define UE4ExtendedLibrary_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Managers_XLAbilityManager_h_9_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__AbilitiesBP() { return STRUCT_OFFSET(UXLAbilityManager, AbilitiesBP); }


#define UE4ExtendedLibrary_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Managers_XLAbilityManager_h_6_PROLOG
#define UE4ExtendedLibrary_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Managers_XLAbilityManager_h_9_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	UE4ExtendedLibrary_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Managers_XLAbilityManager_h_9_PRIVATE_PROPERTY_OFFSET \
	UE4ExtendedLibrary_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Managers_XLAbilityManager_h_9_RPC_WRAPPERS \
	UE4ExtendedLibrary_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Managers_XLAbilityManager_h_9_INCLASS \
	UE4ExtendedLibrary_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Managers_XLAbilityManager_h_9_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define UE4ExtendedLibrary_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Managers_XLAbilityManager_h_9_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	UE4ExtendedLibrary_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Managers_XLAbilityManager_h_9_PRIVATE_PROPERTY_OFFSET \
	UE4ExtendedLibrary_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Managers_XLAbilityManager_h_9_RPC_WRAPPERS_NO_PURE_DECLS \
	UE4ExtendedLibrary_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Managers_XLAbilityManager_h_9_INCLASS_NO_PURE_DECLS \
	UE4ExtendedLibrary_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Managers_XLAbilityManager_h_9_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID UE4ExtendedLibrary_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Managers_XLAbilityManager_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
