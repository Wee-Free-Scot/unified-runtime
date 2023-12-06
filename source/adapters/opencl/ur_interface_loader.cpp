//===--------- ur_interface_loader.cpp - Unified Runtime  ------------===//
//
// Copyright (C) 2023 Intel Corporation
//
// Part of the Unified-Runtime Project, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include <ur_api.h>
#include <ur_ddi.h>

namespace {

// TODO - this is a duplicate of what is in the L0 plugin
// We should move this to somewhere common
ur_result_t validateProcInputs(ur_api_version_t Version, void *pDdiTable) {
  if (nullptr == pDdiTable) {
    return UR_RESULT_ERROR_INVALID_NULL_POINTER;
  }
  // Pre 1.0 we enforce loader and adapter must have same version.
  // Post 1.0 only major version match should be required.
  if (Version != UR_API_VERSION_CURRENT) {
    return UR_RESULT_ERROR_UNSUPPORTED_VERSION;
  }
  return UR_RESULT_SUCCESS;
}
} // namespace

#if defined(__cplusplus)
extern "C" {
#endif

UR_DLLEXPORT ur_result_t UR_APICALL urGetPlatformProcAddrTable(
    ur_api_version_t Version, ur_platform_dditable_t *pDdiTable) {
  auto Result = validateProcInputs(Version, pDdiTable);
  if (UR_RESULT_SUCCESS != Result) {
    return Result;
  }
  pDdiTable->pfnCreateWithNativeHandle = urPlatformCreateWithNativeHandle;
  pDdiTable->pfnGet = urPlatformGet;
  pDdiTable->pfnGetApiVersion = urPlatformGetApiVersion;
  pDdiTable->pfnGetInfo = urPlatformGetInfo;
  pDdiTable->pfnGetNativeHandle = urPlatformGetNativeHandle;
  pDdiTable->pfnGetBackendOption = urPlatformGetBackendOption;
  return UR_RESULT_SUCCESS;
}

UR_DLLEXPORT ur_result_t UR_APICALL urGetContextProcAddrTable(
    ur_api_version_t Version, ur_context_dditable_t *pDdiTable) {
  auto Result = validateProcInputs(Version, pDdiTable);
  if (UR_RESULT_SUCCESS != Result) {
    return Result;
  }
  pDdiTable->pfnCreate = urContextCreate;
  pDdiTable->pfnCreateWithNativeHandle = urContextCreateWithNativeHandle;
  pDdiTable->pfnGetInfo = urContextGetInfo;
  pDdiTable->pfnGetNativeHandle = urContextGetNativeHandle;
  pDdiTable->pfnRelease = urContextRelease;
  pDdiTable->pfnRetain = urContextRetain;
  pDdiTable->pfnSetExtendedDeleter = urContextSetExtendedDeleter;
  return UR_RESULT_SUCCESS;
}

UR_DLLEXPORT ur_result_t UR_APICALL urGetEventProcAddrTable(
    ur_api_version_t Version, ur_event_dditable_t *pDdiTable) {
  auto Result = validateProcInputs(Version, pDdiTable);
  if (UR_RESULT_SUCCESS != Result) {
    return Result;
  }
  pDdiTable->pfnCreateWithNativeHandle = urEventCreateWithNativeHandle;
  pDdiTable->pfnGetInfo = urEventGetInfo;
  pDdiTable->pfnGetNativeHandle = urEventGetNativeHandle;
  pDdiTable->pfnGetProfilingInfo = urEventGetProfilingInfo;
  pDdiTable->pfnRelease = urEventRelease;
  pDdiTable->pfnRetain = urEventRetain;
  pDdiTable->pfnSetCallback = urEventSetCallback;
  pDdiTable->pfnWait = urEventWait;
  return UR_RESULT_SUCCESS;
}

UR_DLLEXPORT ur_result_t UR_APICALL urGetProgramProcAddrTable(
    ur_api_version_t Version, ur_program_dditable_t *pDdiTable) {
  auto Result = validateProcInputs(Version, pDdiTable);
  if (UR_RESULT_SUCCESS != Result) {
    return Result;
  }
  pDdiTable->pfnBuild = urProgramBuild;
  pDdiTable->pfnCompile = urProgramCompile;
  pDdiTable->pfnCreateWithBinary = urProgramCreateWithBinary;
  pDdiTable->pfnCreateWithIL = urProgramCreateWithIL;
  pDdiTable->pfnCreateWithNativeHandle = urProgramCreateWithNativeHandle;
  pDdiTable->pfnGetBuildInfo = urProgramGetBuildInfo;
  pDdiTable->pfnGetFunctionPointer = urProgramGetFunctionPointer;
  pDdiTable->pfnGetInfo = urProgramGetInfo;
  pDdiTable->pfnGetNativeHandle = urProgramGetNativeHandle;
  pDdiTable->pfnLink = urProgramLink;
  pDdiTable->pfnRelease = urProgramRelease;
  pDdiTable->pfnRetain = urProgramRetain;
  pDdiTable->pfnSetSpecializationConstants =
      urProgramSetSpecializationConstants;
  return UR_RESULT_SUCCESS;
}

UR_DLLEXPORT ur_result_t UR_APICALL urGetKernelProcAddrTable(
    ur_api_version_t Version, ur_kernel_dditable_t *pDdiTable) {
  auto Result = validateProcInputs(Version, pDdiTable);
  if (UR_RESULT_SUCCESS != Result) {
    return Result;
  }
  pDdiTable->pfnCreate = urKernelCreate;
  pDdiTable->pfnCreateWithNativeHandle = urKernelCreateWithNativeHandle;
  pDdiTable->pfnGetGroupInfo = urKernelGetGroupInfo;
  pDdiTable->pfnGetInfo = urKernelGetInfo;
  pDdiTable->pfnGetNativeHandle = urKernelGetNativeHandle;
  pDdiTable->pfnGetSubGroupInfo = urKernelGetSubGroupInfo;
  pDdiTable->pfnRelease = urKernelRelease;
  pDdiTable->pfnRetain = urKernelRetain;
  pDdiTable->pfnSetArgLocal = urKernelSetArgLocal;
  pDdiTable->pfnSetArgMemObj = urKernelSetArgMemObj;
  pDdiTable->pfnSetArgPointer = urKernelSetArgPointer;
  pDdiTable->pfnSetArgSampler = urKernelSetArgSampler;
  pDdiTable->pfnSetArgValue = urKernelSetArgValue;
  pDdiTable->pfnSetExecInfo = urKernelSetExecInfo;
  pDdiTable->pfnSetSpecializationConstants = nullptr;
  return UR_RESULT_SUCCESS;
}

UR_DLLEXPORT ur_result_t UR_APICALL urGetSamplerProcAddrTable(
    ur_api_version_t Version, ur_sampler_dditable_t *pDdiTable) {
  auto Result = validateProcInputs(Version, pDdiTable);
  if (UR_RESULT_SUCCESS != Result) {
    return Result;
  }
  pDdiTable->pfnCreate = urSamplerCreate;
  pDdiTable->pfnCreateWithNativeHandle = urSamplerCreateWithNativeHandle;
  pDdiTable->pfnGetInfo = urSamplerGetInfo;
  pDdiTable->pfnGetNativeHandle = urSamplerGetNativeHandle;
  pDdiTable->pfnRelease = urSamplerRelease;
  pDdiTable->pfnRetain = urSamplerRetain;
  return UR_RESULT_SUCCESS;
}

UR_DLLEXPORT ur_result_t UR_APICALL
urGetMemProcAddrTable(ur_api_version_t Version, ur_mem_dditable_t *pDdiTable) {
  auto Result = validateProcInputs(Version, pDdiTable);
  if (UR_RESULT_SUCCESS != Result) {
    return Result;
  }
  pDdiTable->pfnBufferCreate = urMemBufferCreate;
  pDdiTable->pfnBufferPartition = urMemBufferPartition;
  pDdiTable->pfnBufferCreateWithNativeHandle =
      urMemBufferCreateWithNativeHandle;
  pDdiTable->pfnGetInfo = urMemGetInfo;
  pDdiTable->pfnGetNativeHandle = urMemGetNativeHandle;
  pDdiTable->pfnImageCreate = urMemImageCreate;
  pDdiTable->pfnImageGetInfo = urMemImageGetInfo;
  pDdiTable->pfnRelease = urMemRelease;
  pDdiTable->pfnRetain = urMemRetain;
  return UR_RESULT_SUCCESS;
}

UR_DLLEXPORT ur_result_t UR_APICALL urGetEnqueueProcAddrTable(
    ur_api_version_t Version, ur_enqueue_dditable_t *pDdiTable) {
  auto Result = validateProcInputs(Version, pDdiTable);
  if (UR_RESULT_SUCCESS != Result) {
    return Result;
  }
  pDdiTable->pfnDeviceGlobalVariableRead = urEnqueueDeviceGlobalVariableRead;
  pDdiTable->pfnDeviceGlobalVariableWrite = urEnqueueDeviceGlobalVariableWrite;
  pDdiTable->pfnEventsWait = urEnqueueEventsWait;
  pDdiTable->pfnEventsWaitWithBarrier = urEnqueueEventsWaitWithBarrier;
  pDdiTable->pfnKernelLaunch = urEnqueueKernelLaunch;
  pDdiTable->pfnMemBufferCopy = urEnqueueMemBufferCopy;
  pDdiTable->pfnMemBufferCopyRect = urEnqueueMemBufferCopyRect;
  pDdiTable->pfnMemBufferFill = urEnqueueMemBufferFill;
  pDdiTable->pfnMemBufferMap = urEnqueueMemBufferMap;
  pDdiTable->pfnMemBufferRead = urEnqueueMemBufferRead;
  pDdiTable->pfnMemBufferReadRect = urEnqueueMemBufferReadRect;
  pDdiTable->pfnMemBufferWrite = urEnqueueMemBufferWrite;
  pDdiTable->pfnMemBufferWriteRect = urEnqueueMemBufferWriteRect;
  pDdiTable->pfnMemImageCopy = urEnqueueMemImageCopy;
  pDdiTable->pfnMemImageRead = urEnqueueMemImageRead;
  pDdiTable->pfnMemImageWrite = urEnqueueMemImageWrite;
  pDdiTable->pfnMemUnmap = urEnqueueMemUnmap;
  pDdiTable->pfnUSMFill2D = urEnqueueUSMFill2D;
  pDdiTable->pfnUSMFill = urEnqueueUSMFill;
  pDdiTable->pfnUSMAdvise = urEnqueueUSMAdvise;
  pDdiTable->pfnUSMMemcpy2D = urEnqueueUSMMemcpy2D;
  pDdiTable->pfnUSMMemcpy = urEnqueueUSMMemcpy;
  pDdiTable->pfnUSMPrefetch = urEnqueueUSMPrefetch;
  pDdiTable->pfnReadHostPipe = urEnqueueReadHostPipe;
  pDdiTable->pfnWriteHostPipe = urEnqueueWriteHostPipe;
  return UR_RESULT_SUCCESS;
}

UR_DLLEXPORT ur_result_t UR_APICALL urGetGlobalProcAddrTable(
    ur_api_version_t Version, ur_global_dditable_t *pDdiTable) {
  auto Result = validateProcInputs(Version, pDdiTable);
  if (UR_RESULT_SUCCESS != Result) {
    return Result;
  }
  pDdiTable->pfnAdapterGet = urAdapterGet;
  pDdiTable->pfnAdapterRelease = urAdapterRelease;
  pDdiTable->pfnAdapterRetain = urAdapterRetain;
  pDdiTable->pfnAdapterGetLastError = urAdapterGetLastError;
  pDdiTable->pfnAdapterGetInfo = urAdapterGetInfo;
  return UR_RESULT_SUCCESS;
}

UR_DLLEXPORT ur_result_t UR_APICALL urGetQueueProcAddrTable(
    ur_api_version_t Version, ur_queue_dditable_t *pDdiTable) {
  auto Result = validateProcInputs(Version, pDdiTable);
  if (UR_RESULT_SUCCESS != Result) {
    return Result;
  }
  pDdiTable->pfnCreate = urQueueCreate;
  pDdiTable->pfnCreateWithNativeHandle = urQueueCreateWithNativeHandle;
  pDdiTable->pfnFinish = urQueueFinish;
  pDdiTable->pfnFlush = urQueueFlush;
  pDdiTable->pfnGetInfo = urQueueGetInfo;
  pDdiTable->pfnGetNativeHandle = urQueueGetNativeHandle;
  pDdiTable->pfnRelease = urQueueRelease;
  pDdiTable->pfnRetain = urQueueRetain;
  return UR_RESULT_SUCCESS;
}

UR_DLLEXPORT ur_result_t UR_APICALL
urGetUSMProcAddrTable(ur_api_version_t Version, ur_usm_dditable_t *pDdiTable) {
  auto Result = validateProcInputs(Version, pDdiTable);
  if (UR_RESULT_SUCCESS != Result) {
    return Result;
  }
  pDdiTable->pfnDeviceAlloc = urUSMDeviceAlloc;
  pDdiTable->pfnFree = urUSMFree;
  pDdiTable->pfnGetMemAllocInfo = urUSMGetMemAllocInfo;
  pDdiTable->pfnHostAlloc = urUSMHostAlloc;
  pDdiTable->pfnPoolCreate = nullptr;
  pDdiTable->pfnPoolRetain = nullptr;
  pDdiTable->pfnPoolRelease = nullptr;
  pDdiTable->pfnPoolGetInfo = nullptr;
  pDdiTable->pfnSharedAlloc = urUSMSharedAlloc;
  return UR_RESULT_SUCCESS;
}

UR_DLLEXPORT ur_result_t UR_APICALL urGetUSMExpProcAddrTable(
    ur_api_version_t Version, ur_usm_exp_dditable_t *pDdiTable) {
  auto Result = validateProcInputs(Version, pDdiTable);
  if (UR_RESULT_SUCCESS != Result) {
    return Result;
  }

  pDdiTable->pfnImportExp = urUSMImportExp;
  pDdiTable->pfnReleaseExp = urUSMReleaseExp;
  return UR_RESULT_SUCCESS;
}

UR_DLLEXPORT ur_result_t UR_APICALL urGetDeviceProcAddrTable(
    ur_api_version_t Version, ur_device_dditable_t *pDdiTable) {
  auto Result = validateProcInputs(Version, pDdiTable);
  if (UR_RESULT_SUCCESS != Result) {
    return Result;
  }
  pDdiTable->pfnCreateWithNativeHandle = urDeviceCreateWithNativeHandle;
  pDdiTable->pfnGet = urDeviceGet;
  pDdiTable->pfnGetGlobalTimestamps = urDeviceGetGlobalTimestamps;
  pDdiTable->pfnGetInfo = urDeviceGetInfo;
  pDdiTable->pfnGetNativeHandle = urDeviceGetNativeHandle;
  pDdiTable->pfnPartition = urDevicePartition;
  pDdiTable->pfnRelease = urDeviceRelease;
  pDdiTable->pfnRetain = urDeviceRetain;
  pDdiTable->pfnSelectBinary = urDeviceSelectBinary;
  return UR_RESULT_SUCCESS;
}

UR_DLLEXPORT ur_result_t UR_APICALL urGetCommandBufferExpProcAddrTable(
    ur_api_version_t version, ur_command_buffer_exp_dditable_t *pDdiTable) {
  auto retVal = validateProcInputs(version, pDdiTable);
  if (UR_RESULT_SUCCESS != retVal) {
    return retVal;
  }
  pDdiTable->pfnCreateExp = urCommandBufferCreateExp;
  pDdiTable->pfnRetainExp = urCommandBufferRetainExp;
  pDdiTable->pfnReleaseExp = urCommandBufferReleaseExp;
  pDdiTable->pfnFinalizeExp = urCommandBufferFinalizeExp;
  pDdiTable->pfnAppendKernelLaunchExp = urCommandBufferAppendKernelLaunchExp;
  pDdiTable->pfnAppendUSMMemcpyExp = urCommandBufferAppendUSMMemcpyExp;
  pDdiTable->pfnAppendMemBufferCopyExp = urCommandBufferAppendMemBufferCopyExp;
  pDdiTable->pfnAppendMemBufferCopyRectExp =
      urCommandBufferAppendMemBufferCopyRectExp;
  pDdiTable->pfnAppendMemBufferReadExp = urCommandBufferAppendMemBufferReadExp;
  pDdiTable->pfnAppendMemBufferReadRectExp =
      urCommandBufferAppendMemBufferReadRectExp;
  pDdiTable->pfnAppendMemBufferWriteExp =
      urCommandBufferAppendMemBufferWriteExp;
  pDdiTable->pfnAppendMemBufferWriteRectExp =
      urCommandBufferAppendMemBufferWriteRectExp;
  pDdiTable->pfnEnqueueExp = urCommandBufferEnqueueExp;

  return retVal;
}

UR_DLLEXPORT ur_result_t UR_APICALL urGetUsmP2PExpProcAddrTable(
    ur_api_version_t version, ur_usm_p2p_exp_dditable_t *pDdiTable) {
  auto retVal = validateProcInputs(version, pDdiTable);
  if (UR_RESULT_SUCCESS != retVal) {
    return retVal;
  }
  pDdiTable->pfnEnablePeerAccessExp = urUsmP2PEnablePeerAccessExp;
  pDdiTable->pfnDisablePeerAccessExp = urUsmP2PDisablePeerAccessExp;
  pDdiTable->pfnPeerAccessGetInfoExp = urUsmP2PPeerAccessGetInfoExp;

  return retVal;
}

UR_DLLEXPORT ur_result_t UR_APICALL urGetBindlessImagesExpProcAddrTable(
    ur_api_version_t version, ur_bindless_images_exp_dditable_t *pDdiTable) {
  auto result = validateProcInputs(version, pDdiTable);
  if (UR_RESULT_SUCCESS != result) {
    return result;
  }
  pDdiTable->pfnUnsampledImageHandleDestroyExp =
      urBindlessImagesUnsampledImageHandleDestroyExp;
  pDdiTable->pfnSampledImageHandleDestroyExp =
      urBindlessImagesSampledImageHandleDestroyExp;
  pDdiTable->pfnImageAllocateExp = urBindlessImagesImageAllocateExp;
  pDdiTable->pfnImageFreeExp = urBindlessImagesImageFreeExp;
  pDdiTable->pfnUnsampledImageCreateExp =
      urBindlessImagesUnsampledImageCreateExp;
  pDdiTable->pfnSampledImageCreateExp = urBindlessImagesSampledImageCreateExp;
  pDdiTable->pfnImageCopyExp = urBindlessImagesImageCopyExp;
  pDdiTable->pfnImageGetInfoExp = urBindlessImagesImageGetInfoExp;
  pDdiTable->pfnMipmapGetLevelExp = urBindlessImagesMipmapGetLevelExp;
  pDdiTable->pfnMipmapFreeExp = urBindlessImagesMipmapFreeExp;
  pDdiTable->pfnImportOpaqueFDExp = urBindlessImagesImportOpaqueFDExp;
  pDdiTable->pfnMapExternalArrayExp = urBindlessImagesMapExternalArrayExp;
  pDdiTable->pfnReleaseInteropExp = urBindlessImagesReleaseInteropExp;
  pDdiTable->pfnImportExternalSemaphoreOpaqueFDExp =
      urBindlessImagesImportExternalSemaphoreOpaqueFDExp;
  pDdiTable->pfnDestroyExternalSemaphoreExp =
      urBindlessImagesDestroyExternalSemaphoreExp;
  pDdiTable->pfnWaitExternalSemaphoreExp =
      urBindlessImagesWaitExternalSemaphoreExp;
  pDdiTable->pfnSignalExternalSemaphoreExp =
      urBindlessImagesSignalExternalSemaphoreExp;
  return UR_RESULT_SUCCESS;
}

UR_DLLEXPORT ur_result_t UR_APICALL urGetVirtualMemProcAddrTable(
    ur_api_version_t version, ur_virtual_mem_dditable_t *pDdiTable) {
  auto retVal = validateProcInputs(version, pDdiTable);
  if (UR_RESULT_SUCCESS != retVal) {
    return retVal;
  }

  pDdiTable->pfnFree = nullptr;
  pDdiTable->pfnGetInfo = nullptr;
  pDdiTable->pfnGranularityGetInfo = nullptr;
  pDdiTable->pfnMap = nullptr;
  pDdiTable->pfnReserve = nullptr;
  pDdiTable->pfnSetAccess = nullptr;
  pDdiTable->pfnUnmap = nullptr;

  return retVal;
}

UR_DLLEXPORT ur_result_t UR_APICALL urGetPhysicalMemProcAddrTable(
    ur_api_version_t version, ur_physical_mem_dditable_t *pDdiTable) {
  auto retVal = validateProcInputs(version, pDdiTable);
  if (UR_RESULT_SUCCESS != retVal) {
    return retVal;
  }

  pDdiTable->pfnCreate = nullptr;
  pDdiTable->pfnRelease = nullptr;
  pDdiTable->pfnRetain = nullptr;

  return retVal;
}

UR_DLLEXPORT ur_result_t UR_APICALL urGetEnqueueExpProcAddrTable(
    ur_api_version_t version, ur_enqueue_exp_dditable_t *pDdiTable) {
  auto result = validateProcInputs(version, pDdiTable);
  if (UR_RESULT_SUCCESS != result) {
    return result;
  }

  pDdiTable->pfnCooperativeKernelLaunchExp = nullptr;

  return UR_RESULT_SUCCESS;
}

UR_DLLEXPORT ur_result_t UR_APICALL urGetKernelExpProcAddrTable(
    ur_api_version_t version, ur_kernel_exp_dditable_t *pDdiTable) {
  auto result = validateProcInputs(version, pDdiTable);
  if (UR_RESULT_SUCCESS != result) {
    return result;
  }

  pDdiTable->pfnSuggestMaxCooperativeGroupCountExp = nullptr;

  return UR_RESULT_SUCCESS;
}

UR_DLLEXPORT ur_result_t UR_APICALL urGetProgramExpProcAddrTable(
    ur_api_version_t version, ur_program_exp_dditable_t *pDdiTable) {
  auto result = validateProcInputs(version, pDdiTable);
  if (UR_RESULT_SUCCESS != result) {
    return result;
  }

  pDdiTable->pfnBuildExp = urProgramBuildExp;
  pDdiTable->pfnCompileExp = urProgramCompileExp;
  pDdiTable->pfnLinkExp = urProgramLinkExp;

  return UR_RESULT_SUCCESS;
}
#if defined(__cplusplus)
} // extern "C"
#endif
