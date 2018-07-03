/*

    This file was generated with gl3w_gen.py, part of gl3w
    (hosted at https://github.com/skaslev/gl3w)

    This is free and unencumbered software released into the public domain.

    Anyone is free to copy, modify, publish, use, compile, sell, or
    distribute this software, either in source code form or as a compiled
    binary, for any purpose, commercial or non-commercial, and by any
    means.

    In jurisdictions that recognize copyright laws, the author or authors
    of this software dedicate any and all copyright interest in the
    software to the public domain. We make this dedication for the benefit
    of the public at large and to the detriment of our heirs and
    successors. We intend this dedication to be an overt act of
    relinquishment in perpetuity of all present and future rights to this
    software under copyright law.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
    IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
    OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
    ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.

*/

#include "gl3w.h"
#include <stdlib.h>

#define ARRAY_SIZE(x)  (sizeof(x) / sizeof((x)[0]))

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>

static HMODULE libgl;
static PROC (__stdcall *wgl_get_proc_address)(LPCSTR);

static int open_libgl(void)
{
	libgl = LoadLibraryA("opengl32.dll");
	if (!libgl)
		return GL3W_ERROR_LIBRARY_OPEN;

	*(void **)(&wgl_get_proc_address) = GetProcAddress(libgl, "wglGetProcAddress");
	return GL3W_OK;
}

static void close_libgl(void)
{
	FreeLibrary(libgl);
}

static GL3WglProc get_proc(const char *proc)
{
	GL3WglProc res;

	res = (GL3WglProc)wgl_get_proc_address(proc);
	if (!res)
		res = (GL3WglProc)GetProcAddress(libgl, proc);
	return res;
}
#elif defined(__APPLE__)
#include <dlfcn.h>

static void *libgl;

static int open_libgl(void)
{
	libgl = dlopen("/System/Library/Frameworks/OpenGL.framework/OpenGL", RTLD_LAZY | RTLD_LOCAL);
	if (!libgl)
		return GL3W_ERROR_LIBRARY_OPEN;

	return GL3W_OK;
}

static void close_libgl(void)
{
	dlclose(libgl);
}

static GL3WglProc get_proc(const char *proc)
{
	GL3WglProc res;

	*(void **)(&res) = dlsym(libgl, proc);
	return res;
}

#else
#include <dlfcn.h>

static void *libgl;
static GL3WglProc (*glx_get_proc_address)(const GLubyte *);

static int open_libgl(void)
{
	libgl = dlopen("libGL.so.1", RTLD_LAZY | RTLD_LOCAL);
	if (!libgl)
		return GL3W_ERROR_LIBRARY_OPEN;

	*(void **)(&glx_get_proc_address) = dlsym(libgl, "glXGetProcAddressARB");
	return GL3W_OK;
}

static void close_libgl(void)
{
	dlclose(libgl);
}

static GL3WglProc get_proc(const char *proc)
{
	GL3WglProc res;

	res = glx_get_proc_address((const GLubyte *)proc);
	if (!res)
		*(void **)(&res) = dlsym(libgl, proc);
	return res;
}
#endif

static struct {
	int major, minor;
} version;

static int parse_version(void)
{
	if (!glGetIntegerv)
		return GL3W_ERROR_INIT;

	glGetIntegerv(GL_MAJOR_VERSION, &version.major);
	glGetIntegerv(GL_MINOR_VERSION, &version.minor);

	if (version.major < 3)
		return GL3W_ERROR_OPENGL_VERSION;
	return GL3W_OK;
}

static void load_procs(GL3WGetProcAddressProc proc);

int gl3wInit(void)
{
	return gl3wInit2(get_proc);
}

int gl3wInit2(GL3WGetProcAddressProc proc)
{
	int res = open_libgl();
	if (res)
		return res;

	atexit(close_libgl);
	load_procs(proc);
	return parse_version();
}

int gl3wIsSupported(int major, int minor)
{
	if (major < 3)
		return 0;
	if (version.major == major)
		return version.minor >= minor;
	return version.major >= major;
}

GL3WglProc gl3wGetProcAddress(const char *proc)
{
	return get_proc(proc);
}

static const char *proc_names[] = {
	"glActiveProgramEXT",
	"glActiveShaderProgram",
	"glActiveTexture",
	"glApplyFramebufferAttachmentCMAAINTEL",
	"glAttachShader",
	"glBeginConditionalRender",
	"glBeginConditionalRenderNV",
	"glBeginPerfMonitorAMD",
	"glBeginPerfQueryINTEL",
	"glBeginQuery",
	"glBeginQueryIndexed",
	"glBeginTransformFeedback",
	"glBindAttribLocation",
	"glBindBuffer",
	"glBindBufferBase",
	"glBindBufferRange",
	"glBindBuffersBase",
	"glBindBuffersRange",
	"glBindFragDataLocation",
	"glBindFragDataLocationIndexed",
	"glBindFramebuffer",
	"glBindImageTexture",
	"glBindImageTextures",
	"glBindMultiTextureEXT",
	"glBindProgramPipeline",
	"glBindRenderbuffer",
	"glBindSampler",
	"glBindSamplers",
	"glBindTexture",
	"glBindTextureUnit",
	"glBindTextures",
	"glBindTransformFeedback",
	"glBindVertexArray",
	"glBindVertexBuffer",
	"glBindVertexBuffers",
	"glBlendBarrierKHR",
	"glBlendBarrierNV",
	"glBlendColor",
	"glBlendEquation",
	"glBlendEquationSeparate",
	"glBlendEquationSeparatei",
	"glBlendEquationSeparateiARB",
	"glBlendEquationi",
	"glBlendEquationiARB",
	"glBlendFunc",
	"glBlendFuncSeparate",
	"glBlendFuncSeparatei",
	"glBlendFuncSeparateiARB",
	"glBlendFunci",
	"glBlendFunciARB",
	"glBlendParameteriNV",
	"glBlitFramebuffer",
	"glBlitNamedFramebuffer",
	"glBufferAddressRangeNV",
	"glBufferData",
	"glBufferPageCommitmentARB",
	"glBufferStorage",
	"glBufferSubData",
	"glCallCommandListNV",
	"glCheckFramebufferStatus",
	"glCheckNamedFramebufferStatus",
	"glCheckNamedFramebufferStatusEXT",
	"glClampColor",
	"glClear",
	"glClearBufferData",
	"glClearBufferSubData",
	"glClearBufferfi",
	"glClearBufferfv",
	"glClearBufferiv",
	"glClearBufferuiv",
	"glClearColor",
	"glClearDepth",
	"glClearDepthf",
	"glClearNamedBufferData",
	"glClearNamedBufferDataEXT",
	"glClearNamedBufferSubData",
	"glClearNamedBufferSubDataEXT",
	"glClearNamedFramebufferfi",
	"glClearNamedFramebufferfv",
	"glClearNamedFramebufferiv",
	"glClearNamedFramebufferuiv",
	"glClearStencil",
	"glClearTexImage",
	"glClearTexSubImage",
	"glClientAttribDefaultEXT",
	"glClientWaitSync",
	"glClipControl",
	"glColorFormatNV",
	"glColorMask",
	"glColorMaski",
	"glCommandListSegmentsNV",
	"glCompileCommandListNV",
	"glCompileShader",
	"glCompileShaderIncludeARB",
	"glCompressedMultiTexImage1DEXT",
	"glCompressedMultiTexImage2DEXT",
	"glCompressedMultiTexImage3DEXT",
	"glCompressedMultiTexSubImage1DEXT",
	"glCompressedMultiTexSubImage2DEXT",
	"glCompressedMultiTexSubImage3DEXT",
	"glCompressedTexImage1D",
	"glCompressedTexImage2D",
	"glCompressedTexImage3D",
	"glCompressedTexSubImage1D",
	"glCompressedTexSubImage2D",
	"glCompressedTexSubImage3D",
	"glCompressedTextureImage1DEXT",
	"glCompressedTextureImage2DEXT",
	"glCompressedTextureImage3DEXT",
	"glCompressedTextureSubImage1D",
	"glCompressedTextureSubImage1DEXT",
	"glCompressedTextureSubImage2D",
	"glCompressedTextureSubImage2DEXT",
	"glCompressedTextureSubImage3D",
	"glCompressedTextureSubImage3DEXT",
	"glConservativeRasterParameterfNV",
	"glConservativeRasterParameteriNV",
	"glCopyBufferSubData",
	"glCopyImageSubData",
	"glCopyMultiTexImage1DEXT",
	"glCopyMultiTexImage2DEXT",
	"glCopyMultiTexSubImage1DEXT",
	"glCopyMultiTexSubImage2DEXT",
	"glCopyMultiTexSubImage3DEXT",
	"glCopyNamedBufferSubData",
	"glCopyPathNV",
	"glCopyTexImage1D",
	"glCopyTexImage2D",
	"glCopyTexSubImage1D",
	"glCopyTexSubImage2D",
	"glCopyTexSubImage3D",
	"glCopyTextureImage1DEXT",
	"glCopyTextureImage2DEXT",
	"glCopyTextureSubImage1D",
	"glCopyTextureSubImage1DEXT",
	"glCopyTextureSubImage2D",
	"glCopyTextureSubImage2DEXT",
	"glCopyTextureSubImage3D",
	"glCopyTextureSubImage3DEXT",
	"glCoverFillPathInstancedNV",
	"glCoverFillPathNV",
	"glCoverStrokePathInstancedNV",
	"glCoverStrokePathNV",
	"glCoverageModulationNV",
	"glCoverageModulationTableNV",
	"glCreateBuffers",
	"glCreateCommandListsNV",
	"glCreateFramebuffers",
	"glCreatePerfQueryINTEL",
	"glCreateProgram",
	"glCreateProgramPipelines",
	"glCreateQueries",
	"glCreateRenderbuffers",
	"glCreateSamplers",
	"glCreateShader",
	"glCreateShaderProgramEXT",
	"glCreateShaderProgramv",
	"glCreateStatesNV",
	"glCreateSyncFromCLeventARB",
	"glCreateTextures",
	"glCreateTransformFeedbacks",
	"glCreateVertexArrays",
	"glCullFace",
	"glDebugMessageCallback",
	"glDebugMessageCallbackARB",
	"glDebugMessageControl",
	"glDebugMessageControlARB",
	"glDebugMessageInsert",
	"glDebugMessageInsertARB",
	"glDeleteBuffers",
	"glDeleteCommandListsNV",
	"glDeleteFramebuffers",
	"glDeleteNamedStringARB",
	"glDeletePathsNV",
	"glDeletePerfMonitorsAMD",
	"glDeletePerfQueryINTEL",
	"glDeleteProgram",
	"glDeleteProgramPipelines",
	"glDeleteQueries",
	"glDeleteRenderbuffers",
	"glDeleteSamplers",
	"glDeleteShader",
	"glDeleteStatesNV",
	"glDeleteSync",
	"glDeleteTextures",
	"glDeleteTransformFeedbacks",
	"glDeleteVertexArrays",
	"glDepthFunc",
	"glDepthMask",
	"glDepthRange",
	"glDepthRangeArrayv",
	"glDepthRangeIndexed",
	"glDepthRangef",
	"glDetachShader",
	"glDisable",
	"glDisableClientStateIndexedEXT",
	"glDisableClientStateiEXT",
	"glDisableIndexedEXT",
	"glDisableVertexArrayAttrib",
	"glDisableVertexArrayAttribEXT",
	"glDisableVertexArrayEXT",
	"glDisableVertexAttribArray",
	"glDisablei",
	"glDispatchCompute",
	"glDispatchComputeGroupSizeARB",
	"glDispatchComputeIndirect",
	"glDrawArrays",
	"glDrawArraysIndirect",
	"glDrawArraysInstanced",
	"glDrawArraysInstancedARB",
	"glDrawArraysInstancedBaseInstance",
	"glDrawArraysInstancedEXT",
	"glDrawBuffer",
	"glDrawBuffers",
	"glDrawCommandsAddressNV",
	"glDrawCommandsNV",
	"glDrawCommandsStatesAddressNV",
	"glDrawCommandsStatesNV",
	"glDrawElements",
	"glDrawElementsBaseVertex",
	"glDrawElementsIndirect",
	"glDrawElementsInstanced",
	"glDrawElementsInstancedARB",
	"glDrawElementsInstancedBaseInstance",
	"glDrawElementsInstancedBaseVertex",
	"glDrawElementsInstancedBaseVertexBaseInstance",
	"glDrawElementsInstancedEXT",
	"glDrawRangeElements",
	"glDrawRangeElementsBaseVertex",
	"glDrawTransformFeedback",
	"glDrawTransformFeedbackInstanced",
	"glDrawTransformFeedbackStream",
	"glDrawTransformFeedbackStreamInstanced",
	"glDrawVkImageNV",
	"glEGLImageTargetTexStorageEXT",
	"glEGLImageTargetTextureStorageEXT",
	"glEdgeFlagFormatNV",
	"glEnable",
	"glEnableClientStateIndexedEXT",
	"glEnableClientStateiEXT",
	"glEnableIndexedEXT",
	"glEnableVertexArrayAttrib",
	"glEnableVertexArrayAttribEXT",
	"glEnableVertexArrayEXT",
	"glEnableVertexAttribArray",
	"glEnablei",
	"glEndConditionalRender",
	"glEndConditionalRenderNV",
	"glEndPerfMonitorAMD",
	"glEndPerfQueryINTEL",
	"glEndQuery",
	"glEndQueryIndexed",
	"glEndTransformFeedback",
	"glEvaluateDepthValuesARB",
	"glFenceSync",
	"glFinish",
	"glFlush",
	"glFlushMappedBufferRange",
	"glFlushMappedNamedBufferRange",
	"glFlushMappedNamedBufferRangeEXT",
	"glFogCoordFormatNV",
	"glFragmentCoverageColorNV",
	"glFramebufferDrawBufferEXT",
	"glFramebufferDrawBuffersEXT",
	"glFramebufferFetchBarrierEXT",
	"glFramebufferParameteri",
	"glFramebufferReadBufferEXT",
	"glFramebufferRenderbuffer",
	"glFramebufferSampleLocationsfvARB",
	"glFramebufferSampleLocationsfvNV",
	"glFramebufferTexture",
	"glFramebufferTexture1D",
	"glFramebufferTexture2D",
	"glFramebufferTexture3D",
	"glFramebufferTextureARB",
	"glFramebufferTextureFaceARB",
	"glFramebufferTextureLayer",
	"glFramebufferTextureLayerARB",
	"glFramebufferTextureMultiviewOVR",
	"glFrontFace",
	"glGenBuffers",
	"glGenFramebuffers",
	"glGenPathsNV",
	"glGenPerfMonitorsAMD",
	"glGenProgramPipelines",
	"glGenQueries",
	"glGenRenderbuffers",
	"glGenSamplers",
	"glGenTextures",
	"glGenTransformFeedbacks",
	"glGenVertexArrays",
	"glGenerateMipmap",
	"glGenerateMultiTexMipmapEXT",
	"glGenerateTextureMipmap",
	"glGenerateTextureMipmapEXT",
	"glGetActiveAtomicCounterBufferiv",
	"glGetActiveAttrib",
	"glGetActiveSubroutineName",
	"glGetActiveSubroutineUniformName",
	"glGetActiveSubroutineUniformiv",
	"glGetActiveUniform",
	"glGetActiveUniformBlockName",
	"glGetActiveUniformBlockiv",
	"glGetActiveUniformName",
	"glGetActiveUniformsiv",
	"glGetAttachedShaders",
	"glGetAttribLocation",
	"glGetBooleanIndexedvEXT",
	"glGetBooleani_v",
	"glGetBooleanv",
	"glGetBufferParameteri64v",
	"glGetBufferParameteriv",
	"glGetBufferParameterui64vNV",
	"glGetBufferPointerv",
	"glGetBufferSubData",
	"glGetCommandHeaderNV",
	"glGetCompressedMultiTexImageEXT",
	"glGetCompressedTexImage",
	"glGetCompressedTextureImage",
	"glGetCompressedTextureImageEXT",
	"glGetCompressedTextureSubImage",
	"glGetCoverageModulationTableNV",
	"glGetDebugMessageLog",
	"glGetDebugMessageLogARB",
	"glGetDoubleIndexedvEXT",
	"glGetDoublei_v",
	"glGetDoublei_vEXT",
	"glGetDoublev",
	"glGetError",
	"glGetFirstPerfQueryIdINTEL",
	"glGetFloatIndexedvEXT",
	"glGetFloati_v",
	"glGetFloati_vEXT",
	"glGetFloatv",
	"glGetFragDataIndex",
	"glGetFragDataLocation",
	"glGetFramebufferAttachmentParameteriv",
	"glGetFramebufferParameteriv",
	"glGetFramebufferParameterivEXT",
	"glGetGraphicsResetStatus",
	"glGetGraphicsResetStatusARB",
	"glGetImageHandleARB",
	"glGetImageHandleNV",
	"glGetInteger64i_v",
	"glGetInteger64v",
	"glGetIntegerIndexedvEXT",
	"glGetIntegeri_v",
	"glGetIntegerui64i_vNV",
	"glGetIntegerui64vNV",
	"glGetIntegerv",
	"glGetInternalformatSampleivNV",
	"glGetInternalformati64v",
	"glGetInternalformativ",
	"glGetMultiTexEnvfvEXT",
	"glGetMultiTexEnvivEXT",
	"glGetMultiTexGendvEXT",
	"glGetMultiTexGenfvEXT",
	"glGetMultiTexGenivEXT",
	"glGetMultiTexImageEXT",
	"glGetMultiTexLevelParameterfvEXT",
	"glGetMultiTexLevelParameterivEXT",
	"glGetMultiTexParameterIivEXT",
	"glGetMultiTexParameterIuivEXT",
	"glGetMultiTexParameterfvEXT",
	"glGetMultiTexParameterivEXT",
	"glGetMultisamplefv",
	"glGetNamedBufferParameteri64v",
	"glGetNamedBufferParameteriv",
	"glGetNamedBufferParameterivEXT",
	"glGetNamedBufferParameterui64vNV",
	"glGetNamedBufferPointerv",
	"glGetNamedBufferPointervEXT",
	"glGetNamedBufferSubData",
	"glGetNamedBufferSubDataEXT",
	"glGetNamedFramebufferAttachmentParameteriv",
	"glGetNamedFramebufferAttachmentParameterivEXT",
	"glGetNamedFramebufferParameteriv",
	"glGetNamedFramebufferParameterivEXT",
	"glGetNamedProgramLocalParameterIivEXT",
	"glGetNamedProgramLocalParameterIuivEXT",
	"glGetNamedProgramLocalParameterdvEXT",
	"glGetNamedProgramLocalParameterfvEXT",
	"glGetNamedProgramStringEXT",
	"glGetNamedProgramivEXT",
	"glGetNamedRenderbufferParameteriv",
	"glGetNamedRenderbufferParameterivEXT",
	"glGetNamedStringARB",
	"glGetNamedStringivARB",
	"glGetNextPerfQueryIdINTEL",
	"glGetObjectLabel",
	"glGetObjectLabelEXT",
	"glGetObjectPtrLabel",
	"glGetPathCommandsNV",
	"glGetPathCoordsNV",
	"glGetPathDashArrayNV",
	"glGetPathLengthNV",
	"glGetPathMetricRangeNV",
	"glGetPathMetricsNV",
	"glGetPathParameterfvNV",
	"glGetPathParameterivNV",
	"glGetPathSpacingNV",
	"glGetPerfCounterInfoINTEL",
	"glGetPerfMonitorCounterDataAMD",
	"glGetPerfMonitorCounterInfoAMD",
	"glGetPerfMonitorCounterStringAMD",
	"glGetPerfMonitorCountersAMD",
	"glGetPerfMonitorGroupStringAMD",
	"glGetPerfMonitorGroupsAMD",
	"glGetPerfQueryDataINTEL",
	"glGetPerfQueryIdByNameINTEL",
	"glGetPerfQueryInfoINTEL",
	"glGetPointerIndexedvEXT",
	"glGetPointeri_vEXT",
	"glGetPointerv",
	"glGetProgramBinary",
	"glGetProgramInfoLog",
	"glGetProgramInterfaceiv",
	"glGetProgramPipelineInfoLog",
	"glGetProgramPipelineiv",
	"glGetProgramResourceIndex",
	"glGetProgramResourceLocation",
	"glGetProgramResourceLocationIndex",
	"glGetProgramResourceName",
	"glGetProgramResourcefvNV",
	"glGetProgramResourceiv",
	"glGetProgramStageiv",
	"glGetProgramiv",
	"glGetQueryBufferObjecti64v",
	"glGetQueryBufferObjectiv",
	"glGetQueryBufferObjectui64v",
	"glGetQueryBufferObjectuiv",
	"glGetQueryIndexediv",
	"glGetQueryObjecti64v",
	"glGetQueryObjectiv",
	"glGetQueryObjectui64v",
	"glGetQueryObjectuiv",
	"glGetQueryiv",
	"glGetRenderbufferParameteriv",
	"glGetSamplerParameterIiv",
	"glGetSamplerParameterIuiv",
	"glGetSamplerParameterfv",
	"glGetSamplerParameteriv",
	"glGetShaderInfoLog",
	"glGetShaderPrecisionFormat",
	"glGetShaderSource",
	"glGetShaderiv",
	"glGetStageIndexNV",
	"glGetString",
	"glGetStringi",
	"glGetSubroutineIndex",
	"glGetSubroutineUniformLocation",
	"glGetSynciv",
	"glGetTexImage",
	"glGetTexLevelParameterfv",
	"glGetTexLevelParameteriv",
	"glGetTexParameterIiv",
	"glGetTexParameterIuiv",
	"glGetTexParameterfv",
	"glGetTexParameteriv",
	"glGetTextureHandleARB",
	"glGetTextureHandleNV",
	"glGetTextureImage",
	"glGetTextureImageEXT",
	"glGetTextureLevelParameterfv",
	"glGetTextureLevelParameterfvEXT",
	"glGetTextureLevelParameteriv",
	"glGetTextureLevelParameterivEXT",
	"glGetTextureParameterIiv",
	"glGetTextureParameterIivEXT",
	"glGetTextureParameterIuiv",
	"glGetTextureParameterIuivEXT",
	"glGetTextureParameterfv",
	"glGetTextureParameterfvEXT",
	"glGetTextureParameteriv",
	"glGetTextureParameterivEXT",
	"glGetTextureSamplerHandleARB",
	"glGetTextureSamplerHandleNV",
	"glGetTextureSubImage",
	"glGetTransformFeedbackVarying",
	"glGetTransformFeedbacki64_v",
	"glGetTransformFeedbacki_v",
	"glGetTransformFeedbackiv",
	"glGetUniformBlockIndex",
	"glGetUniformIndices",
	"glGetUniformLocation",
	"glGetUniformSubroutineuiv",
	"glGetUniformdv",
	"glGetUniformfv",
	"glGetUniformi64vARB",
	"glGetUniformi64vNV",
	"glGetUniformiv",
	"glGetUniformui64vARB",
	"glGetUniformui64vNV",
	"glGetUniformuiv",
	"glGetVertexArrayIndexed64iv",
	"glGetVertexArrayIndexediv",
	"glGetVertexArrayIntegeri_vEXT",
	"glGetVertexArrayIntegervEXT",
	"glGetVertexArrayPointeri_vEXT",
	"glGetVertexArrayPointervEXT",
	"glGetVertexArrayiv",
	"glGetVertexAttribIiv",
	"glGetVertexAttribIuiv",
	"glGetVertexAttribLdv",
	"glGetVertexAttribLi64vNV",
	"glGetVertexAttribLui64vARB",
	"glGetVertexAttribLui64vNV",
	"glGetVertexAttribPointerv",
	"glGetVertexAttribdv",
	"glGetVertexAttribfv",
	"glGetVertexAttribiv",
	"glGetVkProcAddrNV",
	"glGetnCompressedTexImage",
	"glGetnCompressedTexImageARB",
	"glGetnTexImage",
	"glGetnTexImageARB",
	"glGetnUniformdv",
	"glGetnUniformdvARB",
	"glGetnUniformfv",
	"glGetnUniformfvARB",
	"glGetnUniformi64vARB",
	"glGetnUniformiv",
	"glGetnUniformivARB",
	"glGetnUniformui64vARB",
	"glGetnUniformuiv",
	"glGetnUniformuivARB",
	"glHint",
	"glIndexFormatNV",
	"glInsertEventMarkerEXT",
	"glInterpolatePathsNV",
	"glInvalidateBufferData",
	"glInvalidateBufferSubData",
	"glInvalidateFramebuffer",
	"glInvalidateNamedFramebufferData",
	"glInvalidateNamedFramebufferSubData",
	"glInvalidateSubFramebuffer",
	"glInvalidateTexImage",
	"glInvalidateTexSubImage",
	"glIsBuffer",
	"glIsBufferResidentNV",
	"glIsCommandListNV",
	"glIsEnabled",
	"glIsEnabledIndexedEXT",
	"glIsEnabledi",
	"glIsFramebuffer",
	"glIsImageHandleResidentARB",
	"glIsImageHandleResidentNV",
	"glIsNamedBufferResidentNV",
	"glIsNamedStringARB",
	"glIsPathNV",
	"glIsPointInFillPathNV",
	"glIsPointInStrokePathNV",
	"glIsProgram",
	"glIsProgramPipeline",
	"glIsQuery",
	"glIsRenderbuffer",
	"glIsSampler",
	"glIsShader",
	"glIsStateNV",
	"glIsSync",
	"glIsTexture",
	"glIsTextureHandleResidentARB",
	"glIsTextureHandleResidentNV",
	"glIsTransformFeedback",
	"glIsVertexArray",
	"glLabelObjectEXT",
	"glLineWidth",
	"glLinkProgram",
	"glListDrawCommandsStatesClientNV",
	"glLogicOp",
	"glMakeBufferNonResidentNV",
	"glMakeBufferResidentNV",
	"glMakeImageHandleNonResidentARB",
	"glMakeImageHandleNonResidentNV",
	"glMakeImageHandleResidentARB",
	"glMakeImageHandleResidentNV",
	"glMakeNamedBufferNonResidentNV",
	"glMakeNamedBufferResidentNV",
	"glMakeTextureHandleNonResidentARB",
	"glMakeTextureHandleNonResidentNV",
	"glMakeTextureHandleResidentARB",
	"glMakeTextureHandleResidentNV",
	"glMapBuffer",
	"glMapBufferRange",
	"glMapNamedBuffer",
	"glMapNamedBufferEXT",
	"glMapNamedBufferRange",
	"glMapNamedBufferRangeEXT",
	"glMatrixFrustumEXT",
	"glMatrixLoad3x2fNV",
	"glMatrixLoad3x3fNV",
	"glMatrixLoadIdentityEXT",
	"glMatrixLoadTranspose3x3fNV",
	"glMatrixLoadTransposedEXT",
	"glMatrixLoadTransposefEXT",
	"glMatrixLoaddEXT",
	"glMatrixLoadfEXT",
	"glMatrixMult3x2fNV",
	"glMatrixMult3x3fNV",
	"glMatrixMultTranspose3x3fNV",
	"glMatrixMultTransposedEXT",
	"glMatrixMultTransposefEXT",
	"glMatrixMultdEXT",
	"glMatrixMultfEXT",
	"glMatrixOrthoEXT",
	"glMatrixPopEXT",
	"glMatrixPushEXT",
	"glMatrixRotatedEXT",
	"glMatrixRotatefEXT",
	"glMatrixScaledEXT",
	"glMatrixScalefEXT",
	"glMatrixTranslatedEXT",
	"glMatrixTranslatefEXT",
	"glMaxShaderCompilerThreadsARB",
	"glMaxShaderCompilerThreadsKHR",
	"glMemoryBarrier",
	"glMemoryBarrierByRegion",
	"glMinSampleShading",
	"glMinSampleShadingARB",
	"glMultiDrawArrays",
	"glMultiDrawArraysIndirect",
	"glMultiDrawArraysIndirectBindlessCountNV",
	"glMultiDrawArraysIndirectBindlessNV",
	"glMultiDrawArraysIndirectCount",
	"glMultiDrawArraysIndirectCountARB",
	"glMultiDrawElements",
	"glMultiDrawElementsBaseVertex",
	"glMultiDrawElementsIndirect",
	"glMultiDrawElementsIndirectBindlessCountNV",
	"glMultiDrawElementsIndirectBindlessNV",
	"glMultiDrawElementsIndirectCount",
	"glMultiDrawElementsIndirectCountARB",
	"glMultiTexBufferEXT",
	"glMultiTexCoordPointerEXT",
	"glMultiTexEnvfEXT",
	"glMultiTexEnvfvEXT",
	"glMultiTexEnviEXT",
	"glMultiTexEnvivEXT",
	"glMultiTexGendEXT",
	"glMultiTexGendvEXT",
	"glMultiTexGenfEXT",
	"glMultiTexGenfvEXT",
	"glMultiTexGeniEXT",
	"glMultiTexGenivEXT",
	"glMultiTexImage1DEXT",
	"glMultiTexImage2DEXT",
	"glMultiTexImage3DEXT",
	"glMultiTexParameterIivEXT",
	"glMultiTexParameterIuivEXT",
	"glMultiTexParameterfEXT",
	"glMultiTexParameterfvEXT",
	"glMultiTexParameteriEXT",
	"glMultiTexParameterivEXT",
	"glMultiTexRenderbufferEXT",
	"glMultiTexSubImage1DEXT",
	"glMultiTexSubImage2DEXT",
	"glMultiTexSubImage3DEXT",
	"glNamedBufferData",
	"glNamedBufferDataEXT",
	"glNamedBufferPageCommitmentARB",
	"glNamedBufferPageCommitmentEXT",
	"glNamedBufferStorage",
	"glNamedBufferStorageEXT",
	"glNamedBufferSubData",
	"glNamedBufferSubDataEXT",
	"glNamedCopyBufferSubDataEXT",
	"glNamedFramebufferDrawBuffer",
	"glNamedFramebufferDrawBuffers",
	"glNamedFramebufferParameteri",
	"glNamedFramebufferParameteriEXT",
	"glNamedFramebufferReadBuffer",
	"glNamedFramebufferRenderbuffer",
	"glNamedFramebufferRenderbufferEXT",
	"glNamedFramebufferSampleLocationsfvARB",
	"glNamedFramebufferSampleLocationsfvNV",
	"glNamedFramebufferTexture",
	"glNamedFramebufferTexture1DEXT",
	"glNamedFramebufferTexture2DEXT",
	"glNamedFramebufferTexture3DEXT",
	"glNamedFramebufferTextureEXT",
	"glNamedFramebufferTextureFaceEXT",
	"glNamedFramebufferTextureLayer",
	"glNamedFramebufferTextureLayerEXT",
	"glNamedProgramLocalParameter4dEXT",
	"glNamedProgramLocalParameter4dvEXT",
	"glNamedProgramLocalParameter4fEXT",
	"glNamedProgramLocalParameter4fvEXT",
	"glNamedProgramLocalParameterI4iEXT",
	"glNamedProgramLocalParameterI4ivEXT",
	"glNamedProgramLocalParameterI4uiEXT",
	"glNamedProgramLocalParameterI4uivEXT",
	"glNamedProgramLocalParameters4fvEXT",
	"glNamedProgramLocalParametersI4ivEXT",
	"glNamedProgramLocalParametersI4uivEXT",
	"glNamedProgramStringEXT",
	"glNamedRenderbufferStorage",
	"glNamedRenderbufferStorageEXT",
	"glNamedRenderbufferStorageMultisample",
	"glNamedRenderbufferStorageMultisampleCoverageEXT",
	"glNamedRenderbufferStorageMultisampleEXT",
	"glNamedStringARB",
	"glNormalFormatNV",
	"glObjectLabel",
	"glObjectPtrLabel",
	"glPatchParameterfv",
	"glPatchParameteri",
	"glPathCommandsNV",
	"glPathCoordsNV",
	"glPathCoverDepthFuncNV",
	"glPathDashArrayNV",
	"glPathGlyphIndexArrayNV",
	"glPathGlyphIndexRangeNV",
	"glPathGlyphRangeNV",
	"glPathGlyphsNV",
	"glPathMemoryGlyphIndexArrayNV",
	"glPathParameterfNV",
	"glPathParameterfvNV",
	"glPathParameteriNV",
	"glPathParameterivNV",
	"glPathStencilDepthOffsetNV",
	"glPathStencilFuncNV",
	"glPathStringNV",
	"glPathSubCommandsNV",
	"glPathSubCoordsNV",
	"glPauseTransformFeedback",
	"glPixelStoref",
	"glPixelStorei",
	"glPointAlongPathNV",
	"glPointParameterf",
	"glPointParameterfv",
	"glPointParameteri",
	"glPointParameteriv",
	"glPointSize",
	"glPolygonMode",
	"glPolygonOffset",
	"glPolygonOffsetClamp",
	"glPolygonOffsetClampEXT",
	"glPopDebugGroup",
	"glPopGroupMarkerEXT",
	"glPrimitiveBoundingBoxARB",
	"glPrimitiveRestartIndex",
	"glProgramBinary",
	"glProgramParameteri",
	"glProgramParameteriARB",
	"glProgramPathFragmentInputGenNV",
	"glProgramUniform1d",
	"glProgramUniform1dEXT",
	"glProgramUniform1dv",
	"glProgramUniform1dvEXT",
	"glProgramUniform1f",
	"glProgramUniform1fEXT",
	"glProgramUniform1fv",
	"glProgramUniform1fvEXT",
	"glProgramUniform1i",
	"glProgramUniform1i64ARB",
	"glProgramUniform1i64NV",
	"glProgramUniform1i64vARB",
	"glProgramUniform1i64vNV",
	"glProgramUniform1iEXT",
	"glProgramUniform1iv",
	"glProgramUniform1ivEXT",
	"glProgramUniform1ui",
	"glProgramUniform1ui64ARB",
	"glProgramUniform1ui64NV",
	"glProgramUniform1ui64vARB",
	"glProgramUniform1ui64vNV",
	"glProgramUniform1uiEXT",
	"glProgramUniform1uiv",
	"glProgramUniform1uivEXT",
	"glProgramUniform2d",
	"glProgramUniform2dEXT",
	"glProgramUniform2dv",
	"glProgramUniform2dvEXT",
	"glProgramUniform2f",
	"glProgramUniform2fEXT",
	"glProgramUniform2fv",
	"glProgramUniform2fvEXT",
	"glProgramUniform2i",
	"glProgramUniform2i64ARB",
	"glProgramUniform2i64NV",
	"glProgramUniform2i64vARB",
	"glProgramUniform2i64vNV",
	"glProgramUniform2iEXT",
	"glProgramUniform2iv",
	"glProgramUniform2ivEXT",
	"glProgramUniform2ui",
	"glProgramUniform2ui64ARB",
	"glProgramUniform2ui64NV",
	"glProgramUniform2ui64vARB",
	"glProgramUniform2ui64vNV",
	"glProgramUniform2uiEXT",
	"glProgramUniform2uiv",
	"glProgramUniform2uivEXT",
	"glProgramUniform3d",
	"glProgramUniform3dEXT",
	"glProgramUniform3dv",
	"glProgramUniform3dvEXT",
	"glProgramUniform3f",
	"glProgramUniform3fEXT",
	"glProgramUniform3fv",
	"glProgramUniform3fvEXT",
	"glProgramUniform3i",
	"glProgramUniform3i64ARB",
	"glProgramUniform3i64NV",
	"glProgramUniform3i64vARB",
	"glProgramUniform3i64vNV",
	"glProgramUniform3iEXT",
	"glProgramUniform3iv",
	"glProgramUniform3ivEXT",
	"glProgramUniform3ui",
	"glProgramUniform3ui64ARB",
	"glProgramUniform3ui64NV",
	"glProgramUniform3ui64vARB",
	"glProgramUniform3ui64vNV",
	"glProgramUniform3uiEXT",
	"glProgramUniform3uiv",
	"glProgramUniform3uivEXT",
	"glProgramUniform4d",
	"glProgramUniform4dEXT",
	"glProgramUniform4dv",
	"glProgramUniform4dvEXT",
	"glProgramUniform4f",
	"glProgramUniform4fEXT",
	"glProgramUniform4fv",
	"glProgramUniform4fvEXT",
	"glProgramUniform4i",
	"glProgramUniform4i64ARB",
	"glProgramUniform4i64NV",
	"glProgramUniform4i64vARB",
	"glProgramUniform4i64vNV",
	"glProgramUniform4iEXT",
	"glProgramUniform4iv",
	"glProgramUniform4ivEXT",
	"glProgramUniform4ui",
	"glProgramUniform4ui64ARB",
	"glProgramUniform4ui64NV",
	"glProgramUniform4ui64vARB",
	"glProgramUniform4ui64vNV",
	"glProgramUniform4uiEXT",
	"glProgramUniform4uiv",
	"glProgramUniform4uivEXT",
	"glProgramUniformHandleui64ARB",
	"glProgramUniformHandleui64NV",
	"glProgramUniformHandleui64vARB",
	"glProgramUniformHandleui64vNV",
	"glProgramUniformMatrix2dv",
	"glProgramUniformMatrix2dvEXT",
	"glProgramUniformMatrix2fv",
	"glProgramUniformMatrix2fvEXT",
	"glProgramUniformMatrix2x3dv",
	"glProgramUniformMatrix2x3dvEXT",
	"glProgramUniformMatrix2x3fv",
	"glProgramUniformMatrix2x3fvEXT",
	"glProgramUniformMatrix2x4dv",
	"glProgramUniformMatrix2x4dvEXT",
	"glProgramUniformMatrix2x4fv",
	"glProgramUniformMatrix2x4fvEXT",
	"glProgramUniformMatrix3dv",
	"glProgramUniformMatrix3dvEXT",
	"glProgramUniformMatrix3fv",
	"glProgramUniformMatrix3fvEXT",
	"glProgramUniformMatrix3x2dv",
	"glProgramUniformMatrix3x2dvEXT",
	"glProgramUniformMatrix3x2fv",
	"glProgramUniformMatrix3x2fvEXT",
	"glProgramUniformMatrix3x4dv",
	"glProgramUniformMatrix3x4dvEXT",
	"glProgramUniformMatrix3x4fv",
	"glProgramUniformMatrix3x4fvEXT",
	"glProgramUniformMatrix4dv",
	"glProgramUniformMatrix4dvEXT",
	"glProgramUniformMatrix4fv",
	"glProgramUniformMatrix4fvEXT",
	"glProgramUniformMatrix4x2dv",
	"glProgramUniformMatrix4x2dvEXT",
	"glProgramUniformMatrix4x2fv",
	"glProgramUniformMatrix4x2fvEXT",
	"glProgramUniformMatrix4x3dv",
	"glProgramUniformMatrix4x3dvEXT",
	"glProgramUniformMatrix4x3fv",
	"glProgramUniformMatrix4x3fvEXT",
	"glProgramUniformui64NV",
	"glProgramUniformui64vNV",
	"glProvokingVertex",
	"glPushClientAttribDefaultEXT",
	"glPushDebugGroup",
	"glPushGroupMarkerEXT",
	"glQueryCounter",
	"glRasterSamplesEXT",
	"glReadBuffer",
	"glReadPixels",
	"glReadnPixels",
	"glReadnPixelsARB",
	"glReleaseShaderCompiler",
	"glRenderbufferStorage",
	"glRenderbufferStorageMultisample",
	"glRenderbufferStorageMultisampleCoverageNV",
	"glResolveDepthValuesNV",
	"glResumeTransformFeedback",
	"glSampleCoverage",
	"glSampleMaski",
	"glSamplerParameterIiv",
	"glSamplerParameterIuiv",
	"glSamplerParameterf",
	"glSamplerParameterfv",
	"glSamplerParameteri",
	"glSamplerParameteriv",
	"glScissor",
	"glScissorArrayv",
	"glScissorIndexed",
	"glScissorIndexedv",
	"glSecondaryColorFormatNV",
	"glSelectPerfMonitorCountersAMD",
	"glShaderBinary",
	"glShaderSource",
	"glShaderStorageBlockBinding",
	"glSignalVkFenceNV",
	"glSignalVkSemaphoreNV",
	"glSpecializeShader",
	"glSpecializeShaderARB",
	"glStateCaptureNV",
	"glStencilFillPathInstancedNV",
	"glStencilFillPathNV",
	"glStencilFunc",
	"glStencilFuncSeparate",
	"glStencilMask",
	"glStencilMaskSeparate",
	"glStencilOp",
	"glStencilOpSeparate",
	"glStencilStrokePathInstancedNV",
	"glStencilStrokePathNV",
	"glStencilThenCoverFillPathInstancedNV",
	"glStencilThenCoverFillPathNV",
	"glStencilThenCoverStrokePathInstancedNV",
	"glStencilThenCoverStrokePathNV",
	"glSubpixelPrecisionBiasNV",
	"glTexBuffer",
	"glTexBufferARB",
	"glTexBufferRange",
	"glTexCoordFormatNV",
	"glTexImage1D",
	"glTexImage2D",
	"glTexImage2DMultisample",
	"glTexImage3D",
	"glTexImage3DMultisample",
	"glTexPageCommitmentARB",
	"glTexParameterIiv",
	"glTexParameterIuiv",
	"glTexParameterf",
	"glTexParameterfv",
	"glTexParameteri",
	"glTexParameteriv",
	"glTexStorage1D",
	"glTexStorage2D",
	"glTexStorage2DMultisample",
	"glTexStorage3D",
	"glTexStorage3DMultisample",
	"glTexSubImage1D",
	"glTexSubImage2D",
	"glTexSubImage3D",
	"glTextureBarrier",
	"glTextureBarrierNV",
	"glTextureBuffer",
	"glTextureBufferEXT",
	"glTextureBufferRange",
	"glTextureBufferRangeEXT",
	"glTextureImage1DEXT",
	"glTextureImage2DEXT",
	"glTextureImage3DEXT",
	"glTexturePageCommitmentEXT",
	"glTextureParameterIiv",
	"glTextureParameterIivEXT",
	"glTextureParameterIuiv",
	"glTextureParameterIuivEXT",
	"glTextureParameterf",
	"glTextureParameterfEXT",
	"glTextureParameterfv",
	"glTextureParameterfvEXT",
	"glTextureParameteri",
	"glTextureParameteriEXT",
	"glTextureParameteriv",
	"glTextureParameterivEXT",
	"glTextureRenderbufferEXT",
	"glTextureStorage1D",
	"glTextureStorage1DEXT",
	"glTextureStorage2D",
	"glTextureStorage2DEXT",
	"glTextureStorage2DMultisample",
	"glTextureStorage2DMultisampleEXT",
	"glTextureStorage3D",
	"glTextureStorage3DEXT",
	"glTextureStorage3DMultisample",
	"glTextureStorage3DMultisampleEXT",
	"glTextureSubImage1D",
	"glTextureSubImage1DEXT",
	"glTextureSubImage2D",
	"glTextureSubImage2DEXT",
	"glTextureSubImage3D",
	"glTextureSubImage3DEXT",
	"glTextureView",
	"glTransformFeedbackBufferBase",
	"glTransformFeedbackBufferRange",
	"glTransformFeedbackVaryings",
	"glTransformPathNV",
	"glUniform1d",
	"glUniform1dv",
	"glUniform1f",
	"glUniform1fv",
	"glUniform1i",
	"glUniform1i64ARB",
	"glUniform1i64NV",
	"glUniform1i64vARB",
	"glUniform1i64vNV",
	"glUniform1iv",
	"glUniform1ui",
	"glUniform1ui64ARB",
	"glUniform1ui64NV",
	"glUniform1ui64vARB",
	"glUniform1ui64vNV",
	"glUniform1uiv",
	"glUniform2d",
	"glUniform2dv",
	"glUniform2f",
	"glUniform2fv",
	"glUniform2i",
	"glUniform2i64ARB",
	"glUniform2i64NV",
	"glUniform2i64vARB",
	"glUniform2i64vNV",
	"glUniform2iv",
	"glUniform2ui",
	"glUniform2ui64ARB",
	"glUniform2ui64NV",
	"glUniform2ui64vARB",
	"glUniform2ui64vNV",
	"glUniform2uiv",
	"glUniform3d",
	"glUniform3dv",
	"glUniform3f",
	"glUniform3fv",
	"glUniform3i",
	"glUniform3i64ARB",
	"glUniform3i64NV",
	"glUniform3i64vARB",
	"glUniform3i64vNV",
	"glUniform3iv",
	"glUniform3ui",
	"glUniform3ui64ARB",
	"glUniform3ui64NV",
	"glUniform3ui64vARB",
	"glUniform3ui64vNV",
	"glUniform3uiv",
	"glUniform4d",
	"glUniform4dv",
	"glUniform4f",
	"glUniform4fv",
	"glUniform4i",
	"glUniform4i64ARB",
	"glUniform4i64NV",
	"glUniform4i64vARB",
	"glUniform4i64vNV",
	"glUniform4iv",
	"glUniform4ui",
	"glUniform4ui64ARB",
	"glUniform4ui64NV",
	"glUniform4ui64vARB",
	"glUniform4ui64vNV",
	"glUniform4uiv",
	"glUniformBlockBinding",
	"glUniformHandleui64ARB",
	"glUniformHandleui64NV",
	"glUniformHandleui64vARB",
	"glUniformHandleui64vNV",
	"glUniformMatrix2dv",
	"glUniformMatrix2fv",
	"glUniformMatrix2x3dv",
	"glUniformMatrix2x3fv",
	"glUniformMatrix2x4dv",
	"glUniformMatrix2x4fv",
	"glUniformMatrix3dv",
	"glUniformMatrix3fv",
	"glUniformMatrix3x2dv",
	"glUniformMatrix3x2fv",
	"glUniformMatrix3x4dv",
	"glUniformMatrix3x4fv",
	"glUniformMatrix4dv",
	"glUniformMatrix4fv",
	"glUniformMatrix4x2dv",
	"glUniformMatrix4x2fv",
	"glUniformMatrix4x3dv",
	"glUniformMatrix4x3fv",
	"glUniformSubroutinesuiv",
	"glUniformui64NV",
	"glUniformui64vNV",
	"glUnmapBuffer",
	"glUnmapNamedBuffer",
	"glUnmapNamedBufferEXT",
	"glUseProgram",
	"glUseProgramStages",
	"glUseShaderProgramEXT",
	"glValidateProgram",
	"glValidateProgramPipeline",
	"glVertexArrayAttribBinding",
	"glVertexArrayAttribFormat",
	"glVertexArrayAttribIFormat",
	"glVertexArrayAttribLFormat",
	"glVertexArrayBindVertexBufferEXT",
	"glVertexArrayBindingDivisor",
	"glVertexArrayColorOffsetEXT",
	"glVertexArrayEdgeFlagOffsetEXT",
	"glVertexArrayElementBuffer",
	"glVertexArrayFogCoordOffsetEXT",
	"glVertexArrayIndexOffsetEXT",
	"glVertexArrayMultiTexCoordOffsetEXT",
	"glVertexArrayNormalOffsetEXT",
	"glVertexArraySecondaryColorOffsetEXT",
	"glVertexArrayTexCoordOffsetEXT",
	"glVertexArrayVertexAttribBindingEXT",
	"glVertexArrayVertexAttribDivisorEXT",
	"glVertexArrayVertexAttribFormatEXT",
	"glVertexArrayVertexAttribIFormatEXT",
	"glVertexArrayVertexAttribIOffsetEXT",
	"glVertexArrayVertexAttribLFormatEXT",
	"glVertexArrayVertexAttribLOffsetEXT",
	"glVertexArrayVertexAttribOffsetEXT",
	"glVertexArrayVertexBindingDivisorEXT",
	"glVertexArrayVertexBuffer",
	"glVertexArrayVertexBuffers",
	"glVertexArrayVertexOffsetEXT",
	"glVertexAttrib1d",
	"glVertexAttrib1dv",
	"glVertexAttrib1f",
	"glVertexAttrib1fv",
	"glVertexAttrib1s",
	"glVertexAttrib1sv",
	"glVertexAttrib2d",
	"glVertexAttrib2dv",
	"glVertexAttrib2f",
	"glVertexAttrib2fv",
	"glVertexAttrib2s",
	"glVertexAttrib2sv",
	"glVertexAttrib3d",
	"glVertexAttrib3dv",
	"glVertexAttrib3f",
	"glVertexAttrib3fv",
	"glVertexAttrib3s",
	"glVertexAttrib3sv",
	"glVertexAttrib4Nbv",
	"glVertexAttrib4Niv",
	"glVertexAttrib4Nsv",
	"glVertexAttrib4Nub",
	"glVertexAttrib4Nubv",
	"glVertexAttrib4Nuiv",
	"glVertexAttrib4Nusv",
	"glVertexAttrib4bv",
	"glVertexAttrib4d",
	"glVertexAttrib4dv",
	"glVertexAttrib4f",
	"glVertexAttrib4fv",
	"glVertexAttrib4iv",
	"glVertexAttrib4s",
	"glVertexAttrib4sv",
	"glVertexAttrib4ubv",
	"glVertexAttrib4uiv",
	"glVertexAttrib4usv",
	"glVertexAttribBinding",
	"glVertexAttribDivisor",
	"glVertexAttribDivisorARB",
	"glVertexAttribFormat",
	"glVertexAttribFormatNV",
	"glVertexAttribI1i",
	"glVertexAttribI1iv",
	"glVertexAttribI1ui",
	"glVertexAttribI1uiv",
	"glVertexAttribI2i",
	"glVertexAttribI2iv",
	"glVertexAttribI2ui",
	"glVertexAttribI2uiv",
	"glVertexAttribI3i",
	"glVertexAttribI3iv",
	"glVertexAttribI3ui",
	"glVertexAttribI3uiv",
	"glVertexAttribI4bv",
	"glVertexAttribI4i",
	"glVertexAttribI4iv",
	"glVertexAttribI4sv",
	"glVertexAttribI4ubv",
	"glVertexAttribI4ui",
	"glVertexAttribI4uiv",
	"glVertexAttribI4usv",
	"glVertexAttribIFormat",
	"glVertexAttribIFormatNV",
	"glVertexAttribIPointer",
	"glVertexAttribL1d",
	"glVertexAttribL1dv",
	"glVertexAttribL1i64NV",
	"glVertexAttribL1i64vNV",
	"glVertexAttribL1ui64ARB",
	"glVertexAttribL1ui64NV",
	"glVertexAttribL1ui64vARB",
	"glVertexAttribL1ui64vNV",
	"glVertexAttribL2d",
	"glVertexAttribL2dv",
	"glVertexAttribL2i64NV",
	"glVertexAttribL2i64vNV",
	"glVertexAttribL2ui64NV",
	"glVertexAttribL2ui64vNV",
	"glVertexAttribL3d",
	"glVertexAttribL3dv",
	"glVertexAttribL3i64NV",
	"glVertexAttribL3i64vNV",
	"glVertexAttribL3ui64NV",
	"glVertexAttribL3ui64vNV",
	"glVertexAttribL4d",
	"glVertexAttribL4dv",
	"glVertexAttribL4i64NV",
	"glVertexAttribL4i64vNV",
	"glVertexAttribL4ui64NV",
	"glVertexAttribL4ui64vNV",
	"glVertexAttribLFormat",
	"glVertexAttribLFormatNV",
	"glVertexAttribLPointer",
	"glVertexAttribP1ui",
	"glVertexAttribP1uiv",
	"glVertexAttribP2ui",
	"glVertexAttribP2uiv",
	"glVertexAttribP3ui",
	"glVertexAttribP3uiv",
	"glVertexAttribP4ui",
	"glVertexAttribP4uiv",
	"glVertexAttribPointer",
	"glVertexBindingDivisor",
	"glVertexFormatNV",
	"glViewport",
	"glViewportArrayv",
	"glViewportIndexedf",
	"glViewportIndexedfv",
	"glViewportPositionWScaleNV",
	"glViewportSwizzleNV",
	"glWaitSync",
	"glWaitVkSemaphoreNV",
	"glWeightPathsNV",
	"glWindowRectanglesEXT",
};

union GL3WProcs gl3wProcs;

static void load_procs(GL3WGetProcAddressProc proc)
{
	size_t i;
	for (i = 0; i < ARRAY_SIZE(proc_names); i++)
		gl3wProcs.ptr[i] = proc(proc_names[i]);
}
