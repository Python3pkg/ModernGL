#include "Attribute.hpp"
#include "Buffer.hpp"
#include "BufferAccess.hpp"
#include "ComputeShader.hpp"
#include "Context.hpp"
#include "EnableFlag.hpp"
#include "Error.hpp"
#include "Framebuffer.hpp"
#include "InvalidObject.hpp"
#include "Object.hpp"
#include "Primitive.hpp"
#include "Program.hpp"
#include "ProgramStage.hpp"
#include "Renderbuffer.hpp"
#include "Shader.hpp"
#include "Subroutine.hpp"
#include "SubroutineUniform.hpp"
#include "Texture.hpp"
#include "Uniform.hpp"
#include "UniformBlock.hpp"
#include "Varying.hpp"
#include "VertexArray.hpp"
#include "VertexArrayAttribute.hpp"
#include "VertexArrayListAttribute.hpp"

#include "GLContext.hpp"

MGLContext * create_standalone_context(PyObject * self, PyObject * args) {
	int width;
	int height;

	int args_ok = PyArg_ParseTuple(
		args,
		"II",
		&width,
		&height
	);

	if (!args_ok) {
		return 0;
	}

	MGLContext * ctx = MGLContext_New();

	ctx->gl_context = CreateGLContext(width, height);

	if (PyErr_Occurred()) {
		return 0;
	}

	MGLContext_Initialize(ctx);

	if (PyErr_Occurred()) {
		return 0;
	}

	Py_INCREF(ctx);

	return ctx;
}

MGLContext * create_context(PyObject * self) {
	MGLContext * ctx = MGLContext_New();

	ctx->gl_context = LoadCurrentGLContext();

	if (PyErr_Occurred()) {
		return 0;
	}

	MGLContext_Initialize(ctx);

	if (PyErr_Occurred()) {
		return 0;
	}

	Py_INCREF(ctx);

	return ctx;
}

PyMethodDef MGL_module_methods[] = {
	{"create_standalone_context", (PyCFunction)create_standalone_context, METH_VARARGS, 0},
	{"create_context", (PyCFunction)create_context, METH_NOARGS, 0},
	{0},
};

bool MGL_InitializeModule(PyObject * module) {
	{
		if (PyType_Ready(&MGLAttribute_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register Attribute in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return false;
		}

		Py_INCREF(&MGLAttribute_Type);

		PyModule_AddObject(module, "Attribute", (PyObject *)&MGLAttribute_Type);
	}

	{
		if (PyType_Ready(&MGLBuffer_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register Buffer in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return false;
		}

		Py_INCREF(&MGLBuffer_Type);

		PyModule_AddObject(module, "Buffer", (PyObject *)&MGLBuffer_Type);
	}

	{
		if (PyType_Ready(&MGLBufferAccess_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register BufferAccess in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return false;
		}

		Py_INCREF(&MGLBufferAccess_Type);

		PyModule_AddObject(module, "BufferAccess", (PyObject *)&MGLBufferAccess_Type);
	}

	{
		if (PyType_Ready(&MGLComputeShader_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register ComputeShader in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return false;
		}

		Py_INCREF(&MGLComputeShader_Type);

		PyModule_AddObject(module, "ComputeShader", (PyObject *)&MGLComputeShader_Type);
	}

	{
		if (PyType_Ready(&MGLContext_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register Context in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return false;
		}

		Py_INCREF(&MGLContext_Type);

		PyModule_AddObject(module, "Context", (PyObject *)&MGLContext_Type);
	}

	{
		if (PyType_Ready(&MGLEnableFlag_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register EnableFlag in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return false;
		}

		Py_INCREF(&MGLEnableFlag_Type);

		PyModule_AddObject(module, "EnableFlag", (PyObject *)&MGLEnableFlag_Type);
	}

	{
		if (PyType_Ready(&MGLError_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register Error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return false;
		}

		Py_INCREF(&MGLError_Type);

		PyModule_AddObject(module, "Error", (PyObject *)&MGLError_Type);
	}

	{
		if (PyType_Ready(&MGLFramebuffer_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register Framebuffer in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return false;
		}

		Py_INCREF(&MGLFramebuffer_Type);

		PyModule_AddObject(module, "Framebuffer", (PyObject *)&MGLFramebuffer_Type);
	}

	{
		if (PyType_Ready(&MGLInvalidObject_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register InvalidObject in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return false;
		}

		Py_INCREF(&MGLInvalidObject_Type);

		PyModule_AddObject(module, "InvalidObject", (PyObject *)&MGLInvalidObject_Type);
	}

	{
		if (PyType_Ready(&MGLObject_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register Object in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return false;
		}

		Py_INCREF(&MGLObject_Type);

		PyModule_AddObject(module, "Object", (PyObject *)&MGLObject_Type);
	}

	{
		if (PyType_Ready(&MGLPrimitive_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register Primitive in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return false;
		}

		Py_INCREF(&MGLPrimitive_Type);

		PyModule_AddObject(module, "Primitive", (PyObject *)&MGLPrimitive_Type);
	}

	{
		if (PyType_Ready(&MGLProgram_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register Program in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return false;
		}

		Py_INCREF(&MGLProgram_Type);

		PyModule_AddObject(module, "Program", (PyObject *)&MGLProgram_Type);
	}

	{
		if (PyType_Ready(&MGLProgramStage_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register ProgramStage in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return false;
		}

		Py_INCREF(&MGLProgramStage_Type);

		PyModule_AddObject(module, "ProgramStage", (PyObject *)&MGLProgramStage_Type);
	}

	{
		if (PyType_Ready(&MGLRenderbuffer_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register Renderbuffer in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return false;
		}

		Py_INCREF(&MGLRenderbuffer_Type);

		PyModule_AddObject(module, "Renderbuffer", (PyObject *)&MGLRenderbuffer_Type);
	}

	{
		if (PyType_Ready(&MGLShader_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register Shader in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return false;
		}

		Py_INCREF(&MGLShader_Type);

		PyModule_AddObject(module, "Shader", (PyObject *)&MGLShader_Type);
	}

	{
		if (PyType_Ready(&MGLSubroutine_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register Subroutine in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return false;
		}

		Py_INCREF(&MGLSubroutine_Type);

		PyModule_AddObject(module, "Subroutine", (PyObject *)&MGLSubroutine_Type);
	}

	{
		if (PyType_Ready(&MGLSubroutineUniform_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register SubroutineUniform in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return false;
		}

		Py_INCREF(&MGLSubroutineUniform_Type);

		PyModule_AddObject(module, "SubroutineUniform", (PyObject *)&MGLSubroutineUniform_Type);
	}

	{
		if (PyType_Ready(&MGLTexture_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register Texture in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return false;
		}

		Py_INCREF(&MGLTexture_Type);

		PyModule_AddObject(module, "Texture", (PyObject *)&MGLTexture_Type);
	}

	{
		if (PyType_Ready(&MGLUniform_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register Uniform in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return false;
		}

		Py_INCREF(&MGLUniform_Type);

		PyModule_AddObject(module, "Uniform", (PyObject *)&MGLUniform_Type);
	}

	{
		if (PyType_Ready(&MGLUniformBlock_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register UniformBlock in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return false;
		}

		Py_INCREF(&MGLUniformBlock_Type);

		PyModule_AddObject(module, "UniformBlock", (PyObject *)&MGLUniformBlock_Type);
	}

	{
		if (PyType_Ready(&MGLVarying_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register Varying in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return false;
		}

		Py_INCREF(&MGLVarying_Type);

		PyModule_AddObject(module, "Varying", (PyObject *)&MGLVarying_Type);
	}

	{
		if (PyType_Ready(&MGLVertexArray_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register VertexArray in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return false;
		}

		Py_INCREF(&MGLVertexArray_Type);

		PyModule_AddObject(module, "VertexArray", (PyObject *)&MGLVertexArray_Type);
	}

	{
		if (PyType_Ready(&MGLVertexArrayAttribute_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register VertexArrayAttribute in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return false;
		}

		Py_INCREF(&MGLVertexArrayAttribute_Type);

		PyModule_AddObject(module, "VertexArrayAttribute", (PyObject *)&MGLVertexArrayAttribute_Type);
	}

	{
		if (PyType_Ready(&MGLVertexArrayListAttribute_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register VertexArrayListAttribute in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return false;
		}

		Py_INCREF(&MGLVertexArrayListAttribute_Type);

		PyModule_AddObject(module, "VertexArrayListAttribute", (PyObject *)&MGLVertexArrayListAttribute_Type);
	}

	{
		MGL_TRIANGLES = MGLPrimitive_New();
		MGL_TRIANGLES->name = "TRIANGLES";
		MGL_TRIANGLES->primitive = GL_TRIANGLES;
		MGL_TRIANGLES->geometry_primitive = GL_TRIANGLES;
		MGL_TRIANGLES->transform_primitive = GL_TRIANGLES;
		PyModule_AddObject(module, "TRIANGLES", (PyObject *)MGL_TRIANGLES);

		MGL_TRIANGLE_STRIP = MGLPrimitive_New();
		MGL_TRIANGLE_STRIP->name = "TRIANGLE_STRIP";
		MGL_TRIANGLE_STRIP->primitive = GL_TRIANGLE_STRIP;
		MGL_TRIANGLE_STRIP->geometry_primitive = GL_TRIANGLES;
		MGL_TRIANGLE_STRIP->transform_primitive = GL_TRIANGLES;
		PyModule_AddObject(module, "TRIANGLE_STRIP", (PyObject *)MGL_TRIANGLE_STRIP);

		MGL_TRIANGLE_FAN = MGLPrimitive_New();
		MGL_TRIANGLE_FAN->name = "TRIANGLE_FAN";
		MGL_TRIANGLE_FAN->primitive = GL_TRIANGLE_FAN;
		MGL_TRIANGLE_FAN->geometry_primitive = GL_TRIANGLES;
		MGL_TRIANGLE_FAN->transform_primitive = GL_TRIANGLES;
		PyModule_AddObject(module, "TRIANGLE_FAN", (PyObject *)MGL_TRIANGLE_FAN);

		MGL_LINES = MGLPrimitive_New();
		MGL_LINES->name = "LINES";
		MGL_LINES->primitive = GL_LINES;
		MGL_LINES->geometry_primitive = GL_LINES;
		MGL_LINES->transform_primitive = GL_LINES;
		PyModule_AddObject(module, "LINES", (PyObject *)MGL_LINES);

		MGL_LINE_STRIP = MGLPrimitive_New();
		MGL_LINE_STRIP->name = "LINE_STRIP";
		MGL_LINE_STRIP->primitive = GL_LINE_STRIP;
		MGL_LINE_STRIP->geometry_primitive = GL_LINES;
		MGL_LINE_STRIP->transform_primitive = GL_LINES;
		PyModule_AddObject(module, "LINE_STRIP", (PyObject *)MGL_LINE_STRIP);

		MGL_LINE_LOOP = MGLPrimitive_New();
		MGL_LINE_LOOP->name = "LINE_LOOP";
		MGL_LINE_LOOP->primitive = GL_LINE_LOOP;
		MGL_LINE_LOOP->geometry_primitive = GL_LINES;
		MGL_LINE_LOOP->transform_primitive = GL_LINES;
		PyModule_AddObject(module, "LINE_LOOP", (PyObject *)MGL_LINE_LOOP);

		MGL_POINTS = MGLPrimitive_New();
		MGL_POINTS->name = "POINTS";
		MGL_POINTS->primitive = GL_POINTS;
		MGL_POINTS->geometry_primitive = GL_POINTS;
		MGL_POINTS->transform_primitive = GL_POINTS;
		PyModule_AddObject(module, "POINTS", (PyObject *)MGL_POINTS);

		MGL_LINE_STRIP_ADJACENCY = MGLPrimitive_New();
		MGL_LINE_STRIP_ADJACENCY->name = "LINE_STRIP_ADJACENCY";
		MGL_LINE_STRIP_ADJACENCY->primitive = GL_LINE_STRIP_ADJACENCY;
		MGL_LINE_STRIP_ADJACENCY->geometry_primitive = GL_LINES_ADJACENCY;
		MGL_LINE_STRIP_ADJACENCY->transform_primitive = GL_LINES;
		PyModule_AddObject(module, "LINE_STRIP_ADJACENCY", (PyObject *)MGL_LINE_STRIP_ADJACENCY);

		MGL_LINES_ADJACENCY = MGLPrimitive_New();
		MGL_LINES_ADJACENCY->name = "LINES_ADJACENCY";
		MGL_LINES_ADJACENCY->primitive = GL_LINES_ADJACENCY;
		MGL_LINES_ADJACENCY->geometry_primitive = GL_LINES_ADJACENCY;
		MGL_LINES_ADJACENCY->transform_primitive = GL_LINES;
		PyModule_AddObject(module, "LINES_ADJACENCY", (PyObject *)MGL_LINES_ADJACENCY);

		MGL_TRIANGLE_STRIP_ADJACENCY = MGLPrimitive_New();
		MGL_TRIANGLE_STRIP_ADJACENCY->name = "TRIANGLE_STRIP_ADJACENCY";
		MGL_TRIANGLE_STRIP_ADJACENCY->primitive = GL_TRIANGLE_STRIP_ADJACENCY;
		MGL_TRIANGLE_STRIP_ADJACENCY->geometry_primitive = GL_TRIANGLES_ADJACENCY;
		MGL_TRIANGLE_STRIP_ADJACENCY->transform_primitive = GL_TRIANGLES;
		PyModule_AddObject(module, "TRIANGLE_STRIP_ADJACENCY", (PyObject *)MGL_TRIANGLE_STRIP_ADJACENCY);

		MGL_TRIANGLES_ADJACENCY = MGLPrimitive_New();
		MGL_TRIANGLES_ADJACENCY->name = "TRIANGLES_ADJACENCY";
		MGL_TRIANGLES_ADJACENCY->primitive = GL_TRIANGLES_ADJACENCY;
		MGL_TRIANGLES_ADJACENCY->geometry_primitive = GL_TRIANGLES_ADJACENCY;
		MGL_TRIANGLES_ADJACENCY->transform_primitive = GL_TRIANGLES;
		PyModule_AddObject(module, "TRIANGLES_ADJACENCY", (PyObject *)MGL_TRIANGLES_ADJACENCY);
	}

	{
		MGL_BLEND = MGLEnableFlag_New();
		MGL_BLEND->name = "BLEND";
		MGL_BLEND->flag = GL_BLEND;
		PyModule_AddObject(module, "BLEND", (PyObject *)MGL_BLEND);

		MGL_DEPTH_TEST = MGLEnableFlag_New();
		MGL_DEPTH_TEST->name = "DEPTH_TEST";
		MGL_DEPTH_TEST->flag = GL_DEPTH_TEST;
		PyModule_AddObject(module, "DEPTH_TEST", (PyObject *)MGL_DEPTH_TEST);

		MGL_CULL_FACE = MGLEnableFlag_New();
		MGL_CULL_FACE->name = "CULL_FACE";
		MGL_CULL_FACE->flag = GL_CULL_FACE;
		PyModule_AddObject(module, "CULL_FACE", (PyObject *)MGL_CULL_FACE);

		MGL_MULTISAMPLE = MGLEnableFlag_New();
		MGL_MULTISAMPLE->name = "MULTISAMPLE";
		MGL_MULTISAMPLE->flag = GL_MULTISAMPLE;
		PyModule_AddObject(module, "MULTISAMPLE", (PyObject *)MGL_MULTISAMPLE);
	}

	return true;
}

#if PY_MAJOR_VERSION >= 3

PyModuleDef MGL_moduledef = {
	PyModuleDef_HEAD_INIT,
	"mgl",
	0,
	-1,
	MGL_module_methods,
	0,
	0,
	0,
	0,
};

extern "C" PyObject * PyInit_mgl() {
	PyObject * module = PyModule_Create(&MGL_moduledef);

	if (!MGL_InitializeModule(module)) {
		return 0;
	}

	return module;
}

#else

extern "C" PyObject * initmgl() {
	PyObject * module = Py_InitModule("mgl", MGL_module_methods);

	if (!MGL_InitializeModule(module)) {
		return 0;
	}

	return module;
}

#endif
