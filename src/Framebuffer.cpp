#include "Framebuffer.hpp"

#include "Error.hpp"
#include "InvalidObject.hpp"
#include "Renderbuffer.hpp"
#include "Texture.hpp"

PyObject * MGLFramebuffer_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	MGLFramebuffer * self = (MGLFramebuffer *)type->tp_alloc(type, 0);

	#ifdef MGL_VERBOSE
	printf("MGLFramebuffer_tp_new %p\n", self);
	#endif

	if (self) {
	}

	return (PyObject *)self;
}

void MGLFramebuffer_tp_dealloc(MGLFramebuffer * self) {

	#ifdef MGL_VERBOSE
	printf("MGLFramebuffer_tp_dealloc %p\n", self);
	#endif

	MGLFramebuffer_Type.tp_free((PyObject *)self);
}

int MGLFramebuffer_tp_init(MGLFramebuffer * self, PyObject * args, PyObject * kwargs) {
	MGLError * error = MGLError_FromFormat(TRACE, "Cannot create ModernGL.Framebuffer manually");
	PyErr_SetObject((PyObject *)&MGLError_Type, (PyObject *)error);
	return -1;
}

PyObject * MGLFramebuffer_tp_str(MGLFramebuffer * self) {
	return PyUnicode_FromFormat("<ModernGL.Framebuffer>");
}

PyObject * MGLFramebuffer_release(MGLFramebuffer * self) {
	MGLFramebuffer_Invalidate(self);
	Py_RETURN_NONE;
}

PyObject * MGLFramebuffer_read(MGLFramebuffer * self, PyObject * args) {
	PyObject * viewport;
	int components;
	int floats;

	int args_ok = PyArg_ParseTuple(
		args,
		"OIp",
		&viewport,
		&components,
		&floats
	);

	if (!args_ok) {
		return 0;
	}

	int x;
	int y;
	int width;
	int height;

	if (viewport != Py_None) {
		if (Py_TYPE(viewport) != &PyTuple_Type) {
			MGLError * error = MGLError_FromFormat(TRACE, "the viewport must be a tuple not %s", Py_TYPE(viewport)->tp_name);
			PyErr_SetObject((PyObject *)&MGLError_Type, (PyObject *)error);
			return 0;
		}

		if (PyTuple_GET_SIZE(viewport) == 4) {

			x = PyLong_AsLong(PyTuple_GET_ITEM(viewport, 0));
			y = PyLong_AsLong(PyTuple_GET_ITEM(viewport, 1));
			width = PyLong_AsLong(PyTuple_GET_ITEM(viewport, 2));
			height = PyLong_AsLong(PyTuple_GET_ITEM(viewport, 3));

		} else if (PyTuple_GET_SIZE(viewport) == 2) {

			width = PyLong_AsLong(PyTuple_GET_ITEM(viewport, 0));
			height = PyLong_AsLong(PyTuple_GET_ITEM(viewport, 1));

		} else {

			MGLError * error = MGLError_FromFormat(TRACE, "the viewport size %d is invalid", PyTuple_GET_SIZE(viewport));
			PyErr_SetObject((PyObject *)&MGLError_Type, (PyObject *)error);
			return 0;

		}

		if (PyErr_Occurred()) {
			MGLError * error = MGLError_FromFormat(TRACE, "wrong values in the viewport");
			PyErr_SetObject((PyObject *)&MGLError_Type, (PyObject *)error);
			return 0;
		}

	} else {

		x = 0;
		y = 0;
		width = self->width;
		height = self->height;

	}

	int size = floats ? (width * height * components * 4) : (height * ((width * components + 3) & ~3));
	int type = floats ? GL_FLOAT : GL_UNSIGNED_BYTE;

	const int formats[] = {0, GL_RED, GL_RG, GL_RGB, GL_RGBA};
	int format = formats[components];

	PyObject * result = PyBytes_FromStringAndSize(0, size);
	char * data = PyBytes_AS_STRING(result);

	const GLMethods & gl = self->context->gl;

	gl.BindFramebuffer(GL_FRAMEBUFFER, self->framebuffer_obj);
	gl.ReadPixels(x, y, width, height, format, type, data);
	return result;
}

PyObject * MGLFramebuffer_use(MGLFramebuffer * self) {
	self->context->gl.BindFramebuffer(GL_FRAMEBUFFER, self->framebuffer_obj);
	Py_RETURN_NONE;
}

PyMethodDef MGLFramebuffer_tp_methods[] = {
	{"release", (PyCFunction)MGLFramebuffer_release, METH_NOARGS, 0},
	{"read", (PyCFunction)MGLFramebuffer_read, METH_VARARGS, 0},
	{"use", (PyCFunction)MGLFramebuffer_use, METH_NOARGS, 0},
	{0},
};

PyObject * MGLFramebuffer_get_color_attachments(MGLFramebuffer * self, void * closure) {
	Py_INCREF(self->color_attachments);
	return self->color_attachments;
}

PyObject * MGLFramebuffer_get_depth_attachment(MGLFramebuffer * self, void * closure) {
	Py_INCREF(self->depth_attachment);
	return self->depth_attachment;
}

MGLContext * MGLFramebuffer_get_context(MGLFramebuffer * self, void * closure) {
	Py_INCREF(self->context);
	return self->context;
}

PyGetSetDef MGLFramebuffer_tp_getseters[] = {
	{(char *)"color_attachments", (getter)MGLFramebuffer_get_color_attachments, 0, 0, 0},
	{(char *)"depth_attachment", (getter)MGLFramebuffer_get_depth_attachment, 0, 0, 0},
	{(char *)"context", (getter)MGLFramebuffer_get_context, 0, 0, 0},
	{0},
};

PyTypeObject MGLFramebuffer_Type = {
	PyVarObject_HEAD_INIT(0, 0)
	"mgl.Framebuffer",                                      // tp_name
	sizeof(MGLFramebuffer),                                 // tp_basicsize
	0,                                                      // tp_itemsize
	(destructor)MGLFramebuffer_tp_dealloc,                  // tp_dealloc
	0,                                                      // tp_print
	0,                                                      // tp_getattr
	0,                                                      // tp_setattr
	0,                                                      // tp_reserved
	(reprfunc)MGLFramebuffer_tp_str,                        // tp_repr
	0,                                                      // tp_as_number
	0,                                                      // tp_as_sequence
	0,                                                      // tp_as_mapping
	0,                                                      // tp_hash
	0,                                                      // tp_call
	(reprfunc)MGLFramebuffer_tp_str,                        // tp_str
	0,                                                      // tp_getattro
	0,                                                      // tp_setattro
	0,                                                      // tp_as_buffer
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,               // tp_flags
	0,                                                      // tp_doc
	0,                                                      // tp_traverse
	0,                                                      // tp_clear
	0,                                                      // tp_richcompare
	0,                                                      // tp_weaklistoffset
	0,                                                      // tp_iter
	0,                                                      // tp_iternext
	MGLFramebuffer_tp_methods,                              // tp_methods
	0,                                                      // tp_members
	MGLFramebuffer_tp_getseters,                            // tp_getset
	0,                                                      // tp_base
	0,                                                      // tp_dict
	0,                                                      // tp_descr_get
	0,                                                      // tp_descr_set
	0,                                                      // tp_dictoffset
	(initproc)MGLFramebuffer_tp_init,                       // tp_init
	0,                                                      // tp_alloc
	MGLFramebuffer_tp_new,                                  // tp_new
};

MGLFramebuffer * MGLFramebuffer_New() {
	MGLFramebuffer * self = (MGLFramebuffer *)MGLFramebuffer_tp_new(&MGLFramebuffer_Type, 0, 0);
	return self;
}

void MGLFramebuffer_Invalidate(MGLFramebuffer * framebuffer) {
	if (Py_TYPE(framebuffer) == &MGLInvalidObject_Type) {

		#ifdef MGL_VERBOSE
		printf("MGLFramebuffer_Invalidate %p already released\n", framebuffer);
		#endif

		return;
	}

	#ifdef MGL_VERBOSE
	printf("MGLFramebuffer_Invalidate %p\n", framebuffer);
	#endif

	if (framebuffer->framebuffer_obj) {
		framebuffer->context->gl.DeleteFramebuffers(1, (GLuint *)&framebuffer->framebuffer_obj);

		if (framebuffer->color_attachments) {
			int color_attachments_len = (int)PyTuple_GET_SIZE(framebuffer->color_attachments);

			for (int i = 0; i < color_attachments_len; ++i) {
				PyObject * attachment = PyTuple_GET_ITEM(framebuffer->color_attachments, i);

				if (Py_TYPE(attachment) == &MGLTexture_Type) {
					MGLTexture * texture = (MGLTexture *)attachment;
					if (Py_REFCNT(texture) == 2) {
						MGLTexture_Invalidate(texture);
					}
				} else if (Py_TYPE(attachment) == &MGLRenderbuffer_Type) {
					MGLRenderbuffer * renderbuffer = (MGLRenderbuffer *)attachment;
					if (Py_REFCNT(renderbuffer) == 2) {
						MGLRenderbuffer_Invalidate(renderbuffer);
					}
				}
			}

			Py_DECREF(framebuffer->color_attachments);
		}

		if (framebuffer->depth_attachment) {
			if (Py_TYPE(framebuffer->depth_attachment) == &MGLTexture_Type) {
				MGLTexture * texture = (MGLTexture *)framebuffer->depth_attachment;
				if (Py_REFCNT(texture) == 2) {
					MGLTexture_Invalidate(texture);
				}
			} else if (Py_TYPE(framebuffer->depth_attachment) == &MGLRenderbuffer_Type) {
				MGLRenderbuffer * renderbuffer = (MGLRenderbuffer *)framebuffer->depth_attachment;
				if (Py_REFCNT(renderbuffer) == 2) {
					MGLRenderbuffer_Invalidate(renderbuffer);
				}
			}

			Py_DECREF(framebuffer->depth_attachment);
		}

		Py_DECREF(framebuffer->context);
	}

	Py_TYPE(framebuffer) = &MGLInvalidObject_Type;

	Py_DECREF(framebuffer);
}
