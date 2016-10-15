// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	C++ class header boilerplate exported from UnrealHeaderTool.
	This is automatically generated by the tools.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectBase.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FDamageEvent;
class AController;
class AActor;
#ifdef EXTENDEDLIBRARY_XLCharacter_generated_h
#error "XLCharacter.generated.h already included, missing '#pragma once' in XLCharacter.h"
#endif
#define EXTENDEDLIBRARY_XLCharacter_generated_h

#define TheAristonaut_SneakStreet_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Characters_XLCharacter_h_13_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execDie) \
	{ \
		P_GET_PROPERTY(UFloatProperty,Z_Param_KillingDamage); \
		P_GET_STRUCT_REF(FDamageEvent,Z_Param_Out_DamageEvent); \
		P_GET_OBJECT(AController,Z_Param_Killer); \
		P_GET_OBJECT(AActor,Z_Param_DamageCauser); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=this->Die(Z_Param_KillingDamage,Z_Param_Out_DamageEvent,Z_Param_Killer,Z_Param_DamageCauser); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execTakeDamage) \
	{ \
		P_GET_PROPERTY(UFloatProperty,Z_Param_Damage); \
		P_GET_STRUCT_REF(FDamageEvent,Z_Param_Out_DamageEvent); \
		P_GET_OBJECT(AController,Z_Param_EventInstigator); \
		P_GET_OBJECT(AActor,Z_Param_DamageCauser); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(float*)Z_Param__Result=this->TakeDamage(Z_Param_Damage,Z_Param_Out_DamageEvent,Z_Param_EventInstigator,Z_Param_DamageCauser); \
		P_NATIVE_END; \
	}


#define TheAristonaut_SneakStreet_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Characters_XLCharacter_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execDie) \
	{ \
		P_GET_PROPERTY(UFloatProperty,Z_Param_KillingDamage); \
		P_GET_STRUCT_REF(FDamageEvent,Z_Param_Out_DamageEvent); \
		P_GET_OBJECT(AController,Z_Param_Killer); \
		P_GET_OBJECT(AActor,Z_Param_DamageCauser); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=this->Die(Z_Param_KillingDamage,Z_Param_Out_DamageEvent,Z_Param_Killer,Z_Param_DamageCauser); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execTakeDamage) \
	{ \
		P_GET_PROPERTY(UFloatProperty,Z_Param_Damage); \
		P_GET_STRUCT_REF(FDamageEvent,Z_Param_Out_DamageEvent); \
		P_GET_OBJECT(AController,Z_Param_EventInstigator); \
		P_GET_OBJECT(AActor,Z_Param_DamageCauser); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(float*)Z_Param__Result=this->TakeDamage(Z_Param_Damage,Z_Param_Out_DamageEvent,Z_Param_EventInstigator,Z_Param_DamageCauser); \
		P_NATIVE_END; \
	}


#define TheAristonaut_SneakStreet_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Characters_XLCharacter_h_13_INCLASS_NO_PURE_DECLS \
	private: \
	static void StaticRegisterNativesAXLCharacter(); \
	friend EXTENDEDLIBRARY_API class UClass* Z_Construct_UClass_AXLCharacter(); \
	public: \
	DECLARE_CLASS(AXLCharacter, ACharacter, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/ExtendedLibrary"), NO_API) \
	DECLARE_SERIALIZER(AXLCharacter) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define TheAristonaut_SneakStreet_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Characters_XLCharacter_h_13_INCLASS \
	private: \
	static void StaticRegisterNativesAXLCharacter(); \
	friend EXTENDEDLIBRARY_API class UClass* Z_Construct_UClass_AXLCharacter(); \
	public: \
	DECLARE_CLASS(AXLCharacter, ACharacter, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/ExtendedLibrary"), NO_API) \
	DECLARE_SERIALIZER(AXLCharacter) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define TheAristonaut_SneakStreet_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Characters_XLCharacter_h_13_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AXLCharacter(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AXLCharacter) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AXLCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AXLCharacter); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AXLCharacter(AXLCharacter&&); \
	NO_API AXLCharacter(const AXLCharacter&); \
public:


#define TheAristonaut_SneakStreet_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Characters_XLCharacter_h_13_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AXLCharacter(AXLCharacter&&); \
	NO_API AXLCharacter(const AXLCharacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AXLCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AXLCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AXLCharacter)


#define TheAristonaut_SneakStreet_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Characters_XLCharacter_h_10_PROLOG
#define TheAristonaut_SneakStreet_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Characters_XLCharacter_h_13_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	TheAristonaut_SneakStreet_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Characters_XLCharacter_h_13_RPC_WRAPPERS \
	TheAristonaut_SneakStreet_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Characters_XLCharacter_h_13_INCLASS \
	TheAristonaut_SneakStreet_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Characters_XLCharacter_h_13_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define TheAristonaut_SneakStreet_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Characters_XLCharacter_h_13_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	TheAristonaut_SneakStreet_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Characters_XLCharacter_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
	TheAristonaut_SneakStreet_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Characters_XLCharacter_h_13_INCLASS_NO_PURE_DECLS \
	TheAristonaut_SneakStreet_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Characters_XLCharacter_h_13_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID TheAristonaut_SneakStreet_Plugins_ExtendedLibrary_Source_ExtendedLibrary_Public_Characters_XLCharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
