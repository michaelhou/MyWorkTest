#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef unsigned int UINT32;
typedef unsigned long long UINT64;


#pragma pack(1)
///from base.h
///
/// 128 bit buffer containing a unique identifier value.
/// Unless otherwise specified, aligned on a 64 bit boundary.
///
typedef struct {
  UINT32  Data1;
  UINT16  Data2;
  UINT16  Data3;
  UINT8   Data4[8];
} GUID;

///from UefiBaseType.h
///
/// 128-bit buffer containing a unique identifier value.
///
typedef GUID                      EFI_GUID;

/// from PiFirmwareVolume.h
typedef struct {
  ///
  /// The number of sequential blocks which are of the same size.
  ///
  UINT32 NumBlocks;
  ///
  /// The size of the blocks.
  ///
  UINT32 Length;
} EFI_FV_BLOCK_MAP_ENTRY;
///
/// type of EFI FVB attribute
/// 
typedef UINT32  EFI_FVB_ATTRIBUTES_2;
///
/// Used to verify the integrity of the file.
/// 
typedef union {
  struct {
    ///
    /// The IntegrityCheck.Checksum.Header field is an 8-bit checksum of the file
    /// header. The State and IntegrityCheck.Checksum.File fields are assumed
    /// to be zero and the checksum is calculated such that the entire header sums to zero.
    ///
    UINT8   Header;
    ///
    /// If the FFS_ATTRIB_CHECKSUM (see definition below) bit of the Attributes
    /// field is set to one, the IntegrityCheck.Checksum.File field is an 8-bit
    /// checksum of the file data.
    /// If the FFS_ATTRIB_CHECKSUM bit of the Attributes field is cleared to zero,
    /// the IntegrityCheck.Checksum.File field must be initialized with a value of
    /// 0xAA. The IntegrityCheck.Checksum.File field is valid any time the
    /// EFI_FILE_DATA_VALID bit is set in the State field.
    ///
    UINT8   File;
  } Checksum;
  ///
  /// This is the full 16 bits of the IntegrityCheck field.
  ///
  UINT16    Checksum16;
} EFI_FFS_INTEGRITY_CHECK;
typedef UINT8 EFI_FV_FILETYPE;
typedef UINT8 EFI_FFS_FILE_ATTRIBUTES;
typedef UINT8 EFI_FFS_FILE_STATE;
///
/// Each file begins with the header that describe the 
/// contents and state of the files.
/// 
typedef struct {
  ///
  /// This GUID is the file name. It is used to uniquely identify the file.
  ///
  EFI_GUID                Name;
  ///
  /// Used to verify the integrity of the file.
  ///
  EFI_FFS_INTEGRITY_CHECK IntegrityCheck;
  ///
  /// Identifies the type of file.
  ///
  EFI_FV_FILETYPE         Type;
  ///
  /// Declares various file attribute bits.
  ///
  EFI_FFS_FILE_ATTRIBUTES Attributes;
  ///
  /// The length of the file in bytes, including the FFS header.
  ///
  UINT8                   Size[3];
  ///
  /// Used to track the state of the file throughout the life of the file from creation to deletion.
  ///
  EFI_FFS_FILE_STATE      State;
} EFI_FFS_FILE_HEADER;

///
/// Describes the features and layout of the firmware volume.
///
typedef struct {
  ///
  /// The first 16 bytes are reserved to allow for the reset vector of 
  /// processors whose reset vector is at address 0.
  ///
  UINT8                     ZeroVector[16];
  ///
  /// Declares the file system with which the firmware volume is formatted.
  ///
  EFI_GUID                  FileSystemGuid;
  ///
  /// Length in bytes of the complete firmware volume, including the header.
  ///
  UINT64                    FvLength;
  ///
  /// Set to EFI_FVH_SIGNATURE
  ///
  UINT32                    Signature;
  ///
  /// Declares capabilities and power-on defaults for the firmware volume.
  ///
  EFI_FVB_ATTRIBUTES_2      Attributes;
  ///
  /// Length in bytes of the complete firmware volume header.
  ///
  UINT16                    HeaderLength;
  ///
  /// A 16-bit checksum of the firmware volume header. A valid header sums to zero.
  ///
  UINT16                    Checksum;
  ///
  /// Offset, relative to the start of the header, of the extended header
  /// (EFI_FIRMWARE_VOLUME_EXT_HEADER) or zero if there is no extended header.
  ///
  UINT16                    ExtHeaderOffset;
  ///
  /// This field must always be set to zero.
  ///
  UINT8                     Reserved[1];
  ///
  /// Set to 2. Future versions of this specification may define new header fields and will
  /// increment the Revision field accordingly.
  ///
  UINT8                     Revision;
  ///
  /// An array of run-length encoded FvBlockMapEntry structures. The array is
  /// terminated with an entry of {0,0}.
  ///
  EFI_FV_BLOCK_MAP_ENTRY    BlockMap[1];
} EFI_FIRMWARE_VOLUME_HEADER;

#pragma pack()
#define EFI_FIRMWARE_FILE_SYSTEM2_GUID \
  { 0x8c8ce578, 0x8a3d, 0x4f1c, { 0x99, 0x35, 0x89, 0x61, 0x85, 0xc3, 0x2d, 0xd3 } }

#define CR(record,type,field) ((UINT8*)((UINT8*)(record)-(UINT8*)&((type*)0)->field))