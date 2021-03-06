#include "VertexArray.hpp"

#include "Error.hpp"
#include "InvalidObject.hpp"
#include "Primitive.hpp"
#include "Buffer.hpp"

#include "Attribute.hpp"
#include "VertexArrayAttribute.hpp"
#include "VertexArrayListAttribute.hpp"

#include "ProgramStage.hpp"

PyObject * MGLVertexArray_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	MGLVertexArray * self = (MGLVertexArray *)type->tp_alloc(type, 0);

	#ifdef MGL_VERBOSE
	printf("MGLVertexArray_tp_new %p\n", self);
	#endif

	if (self) {
	}

	return (PyObject *)self;
}

void MGLVertexArray_tp_dealloc(MGLVertexArray * self) {

	#ifdef MGL_VERBOSE
	printf("MGLVertexArray_tp_dealloc %p\n", self);
	#endif

	MGLVertexArray_Type.tp_free((PyObject *)self);
}

int MGLVertexArray_tp_init(MGLVertexArray * self, PyObject * args, PyObject * kwargs) {
	MGLError * error = MGLError_FromFormat(TRACE, "Cannot create ModernGL.VertexArray manually");
	PyErr_SetObject((PyObject *)&MGLError_Type, (PyObject *)error);
	return -1;
}

PyObject * MGLVertexArray_tp_str(MGLVertexArray * self) {
	return PyUnicode_FromFormat("<ModernGL.VertexArray>");
}

PyObject * MGLVertexArray_render(MGLVertexArray * self, PyObject * args) {
	MGLPrimitive * mode;
	int vertices;
	int first;
	int instances;

	int args_ok = PyArg_ParseTuple(
		args,
		"O!III",
		&MGLPrimitive_Type,
		&mode,
		&vertices,
		&first,
		&instances
	);

	if (!args_ok) {
		return 0;
	}

	if (vertices < 0) {
		if (self->num_vertices < 0) {
			MGLError * error = MGLError_FromFormat(TRACE, "Cannot detect the number of vertices");
			PyErr_SetObject((PyObject *)&MGLError_Type, (PyObject *)error);
			return 0;
		}

		vertices = self->num_vertices;
	}

	MGLPrimitive * gs_input = self->program->geometry_input;

	if (gs_input && gs_input->primitive != mode->geometry_primitive) {
		MGLError * error = MGLError_FromFormat(TRACE, "GeometryShader input is different from render mode");
		PyErr_SetObject((PyObject *)&MGLError_Type, (PyObject *)error);
		return 0;
	}

	const GLMethods & gl = self->context->gl;

	gl.UseProgram(self->program->program_obj);
	gl.BindVertexArray(self->vertex_array_obj);

	if (self->index_buffer != (MGLBuffer *)Py_None) {
		const void * ptr = (const void *)((GLintptr)first * 4);
		gl.DrawElementsInstanced(mode->primitive, vertices, GL_UNSIGNED_INT, ptr, instances);
	} else {
		gl.DrawArraysInstanced(mode->primitive, first, vertices, instances);
	}

	Py_RETURN_NONE;
}

PyObject * MGLVertexArray_transform(MGLVertexArray * self, PyObject * args) {
	MGLBuffer * output;
	MGLPrimitive * mode;
	int vertices;
	int first;
	int instances;

	int args_ok = PyArg_ParseTuple(
		args,
		"O!O!III",
		&MGLBuffer_Type,
		&output,
		&MGLPrimitive_Type,
		&mode,
		&vertices,
		&first,
		&instances
	);

	if (!args_ok) {
		return 0;
	}

	// TODO: self->program->no_varyings check to save debug time

	if (vertices < 0) {
		if (self->num_vertices < 0) {
			MGLError * error = MGLError_FromFormat(TRACE, "Cannot detect the number of vertices");
			PyErr_SetObject((PyObject *)&MGLError_Type, (PyObject *)error);
			return 0;
		}

		vertices = self->num_vertices;
	}

	MGLPrimitive * gs_input = self->program->geometry_input;

	if (gs_input && gs_input->primitive != mode->geometry_primitive) {
		MGLError * error = MGLError_FromFormat(TRACE, "GeometryShader input is different from transform mode");
		PyErr_SetObject((PyObject *)&MGLError_Type, (PyObject *)error);
		return 0;
	}

	const GLMethods & gl = self->context->gl;

	gl.UseProgram(self->program->program_obj);
	gl.BindVertexArray(self->vertex_array_obj);

	gl.BindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, output->buffer_obj);

	gl.Enable(GL_RASTERIZER_DISCARD);
	gl.BeginTransformFeedback(mode->primitive);

	if (self->subroutine_uniform_locations) {

		unsigned * subroutine_uniform_locations = self->subroutine_uniform_locations;

		if (self->num_vertex_shader_subroutine_uniform_locations) {
			gl.UniformSubroutinesuiv(
				GL_VERTEX_SHADER,
				self->num_vertex_shader_subroutine_uniform_locations,
				subroutine_uniform_locations
			);
			subroutine_uniform_locations += self->num_vertex_shader_subroutine_uniform_locations;
		}

		if (self->num_fragment_shader_subroutine_uniform_locations) {
			gl.UniformSubroutinesuiv(
				GL_FRAGMENT_SHADER,
				self->num_fragment_shader_subroutine_uniform_locations,
				subroutine_uniform_locations
			);
			subroutine_uniform_locations += self->num_fragment_shader_subroutine_uniform_locations;
		}

		if (self->num_geometry_shader_subroutine_uniform_locations) {
			gl.UniformSubroutinesuiv(
				GL_GEOMETRY_SHADER,
				self->num_geometry_shader_subroutine_uniform_locations,
				subroutine_uniform_locations
			);
			subroutine_uniform_locations += self->num_geometry_shader_subroutine_uniform_locations;
		}

		if (self->num_tess_evaluation_shader_subroutine_uniform_locations) {
			gl.UniformSubroutinesuiv(
				GL_TESS_EVALUATION_SHADER,
				self->num_tess_evaluation_shader_subroutine_uniform_locations,
				subroutine_uniform_locations
			);
			subroutine_uniform_locations += self->num_tess_evaluation_shader_subroutine_uniform_locations;
		}

		if (self->num_tess_control_shader_subroutine_uniform_locations) {
			gl.UniformSubroutinesuiv(
				GL_TESS_CONTROL_SHADER,
				self->num_tess_control_shader_subroutine_uniform_locations,
				subroutine_uniform_locations
			);
		}
	}

	if (self->index_buffer != (MGLBuffer *)Py_None) {
		const void * ptr = (const void *)((GLintptr)first * 4);
		gl.DrawElementsInstanced(mode->primitive, vertices, GL_UNSIGNED_INT, ptr, instances);
	} else {
		gl.DrawArraysInstanced(mode->primitive, first, vertices, instances);
	}

	gl.EndTransformFeedback();
	gl.Disable(GL_RASTERIZER_DISCARD);
	gl.Flush();

	Py_RETURN_NONE;
}

PyObject * MGLVertexArray_release(MGLVertexArray * self) {
	MGLVertexArray_Invalidate(self);
	Py_RETURN_NONE;
}

PyMethodDef MGLVertexArray_tp_methods[] = {
	{"render", (PyCFunction)MGLVertexArray_render, METH_VARARGS, 0},
	{"transform", (PyCFunction)MGLVertexArray_transform, METH_VARARGS, 0},
	{"release", (PyCFunction)MGLVertexArray_release, METH_NOARGS, 0},
	{0},
};

MGLProgram * MGLVertexArray_get_program(MGLVertexArray * self, void * closure) {
	Py_INCREF(self->program);
	return self->program;
}

PyObject * MGLVertexArray_get_attributes(MGLVertexArray * self, void * closure) {
	Py_INCREF(self->attributes);
	return self->attributes;
}

PyObject * MGLVertexArray_get_index_buffer(MGLVertexArray * self, void * closure) {
	Py_INCREF(self->index_buffer);
	return (PyObject *)self->index_buffer;
}

int MGLVertexArray_set_index_buffer(MGLVertexArray * self, PyObject * value, void * closure) {
	if (Py_TYPE(value) != &MGLBuffer_Type) {
		MGLError * error = MGLError_FromFormat(TRACE, "index_buffer must be a Buffer not %s", Py_TYPE(value)->tp_name);
		PyErr_SetObject((PyObject *)&MGLError_Type, (PyObject *)error);
		return -1;
	}

	Py_INCREF(value);
	Py_DECREF(self->index_buffer);
	self->index_buffer = (MGLBuffer *)value;
	self->num_vertices = self->index_buffer->size / 4;

	return 0;
}

PyObject * MGLVertexArray_get_vertices(MGLVertexArray * self, void * closure) {
	return PyLong_FromLong(self->num_vertices);
}

int MGLVertexArray_set_vertices(MGLVertexArray * self, PyObject * value, void * closure) {
	int vertices = PyLong_AsUnsignedLong(value);

	if (PyErr_Occurred()) {
		MGLError * error = MGLError_FromFormat(TRACE, "invalid value for vertices");
		PyErr_SetObject((PyObject *)&MGLError_Type, (PyObject *)error);
		return -1;
	}

	self->num_vertices = vertices;

	return 0;
}

int MGLVertexArray_set_subroutines(MGLVertexArray * self, PyObject * value, void * closure) {
	if (PyTuple_GET_SIZE(value) != self->num_subroutine_uniform_locations) {
		MGLError * error = MGLError_FromFormat(TRACE, "the number of subroutines is %d not %d", self->num_subroutine_uniform_locations, PyTuple_GET_SIZE(value));
		PyErr_SetObject((PyObject *)&MGLError_Type, (PyObject *)error);
		return -1;
	}

	for (int i = 0; i < self->num_subroutine_uniform_locations; ++i) {
		self->subroutine_uniform_locations[i] = PyLong_AsUnsignedLong(PyTuple_GET_ITEM(value, i));
	}

	if (PyErr_Occurred()) {
		MGLError * error = MGLError_FromFormat(TRACE, "unsupported values for uniforms");
		PyErr_SetObject((PyObject *)&MGLError_Type, (PyObject *)error);
		return -1;
	}

	return 0;
}

MGLContext * MGLVertexArray_get_context(MGLVertexArray * self, void * closure) {
	Py_INCREF(self->context);
	return self->context;
}

PyGetSetDef MGLVertexArray_tp_getseters[] = {
	{(char *)"program", (getter)MGLVertexArray_get_program, 0, 0, 0},
	{(char *)"attributes", (getter)MGLVertexArray_get_attributes, 0, 0, 0},
	{(char *)"index_buffer", (getter)MGLVertexArray_get_index_buffer, (setter)MGLVertexArray_set_index_buffer, 0, 0},
	{(char *)"vertices", (getter)MGLVertexArray_get_vertices, (setter)MGLVertexArray_set_vertices, 0, 0},
	{(char *)"subroutines", 0, (setter)MGLVertexArray_set_subroutines, 0, 0},
	{(char *)"context", (getter)MGLVertexArray_get_context, 0, 0, 0},
	{0},
};

PyTypeObject MGLVertexArray_Type = {
	PyVarObject_HEAD_INIT(0, 0)
	"mgl.VertexArray",                                      // tp_name
	sizeof(MGLVertexArray),                                 // tp_basicsize
	0,                                                      // tp_itemsize
	(destructor)MGLVertexArray_tp_dealloc,                  // tp_dealloc
	0,                                                      // tp_print
	0,                                                      // tp_getattr
	0,                                                      // tp_setattr
	0,                                                      // tp_reserved
	(reprfunc)MGLVertexArray_tp_str,                        // tp_repr
	0,                                                      // tp_as_number
	0,                                                      // tp_as_sequence
	0,                                                      // tp_as_mapping
	0,                                                      // tp_hash
	0,                                                      // tp_call
	(reprfunc)MGLVertexArray_tp_str,                        // tp_str
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
	MGLVertexArray_tp_methods,                              // tp_methods
	0,                                                      // tp_members
	MGLVertexArray_tp_getseters,                            // tp_getset
	0,                                                      // tp_base
	0,                                                      // tp_dict
	0,                                                      // tp_descr_get
	0,                                                      // tp_descr_set
	0,                                                      // tp_dictoffset
	(initproc)MGLVertexArray_tp_init,                       // tp_init
	0,                                                      // tp_alloc
	MGLVertexArray_tp_new,                                  // tp_new
};

MGLVertexArray * MGLVertexArray_New() {
	MGLVertexArray * self = (MGLVertexArray *)MGLVertexArray_tp_new(&MGLVertexArray_Type, 0, 0);
	return self;
}

void MGLVertexArray_Invalidate(MGLVertexArray * array) {
	if (Py_TYPE(array) == &MGLInvalidObject_Type) {

		#ifdef MGL_VERBOSE
		printf("MGLVertexArray_Invalidate %p already released\n", array);
		#endif

		return;
	}

	#ifdef MGL_VERBOSE
	printf("MGLVertexArray_Invalidate %p\n", array);
	#endif

	const GLMethods & gl = array->context->gl;
	gl.DeleteVertexArrays(1, (GLuint *)&array->vertex_array_obj);

	if (Py_REFCNT(array->program) == 2) {
		MGLProgram_Invalidate(array->program);
	}

	Py_DECREF(array->program);

	if (array->index_buffer != (MGLBuffer *)Py_None) {
		if (Py_REFCNT(array->index_buffer) == 2) {
			MGLBuffer_Invalidate(array->index_buffer);
		}
	}

	Py_DECREF(array->index_buffer);
	Py_DECREF(array->context);

	Py_TYPE(array) = &MGLInvalidObject_Type;

	Py_DECREF(array);
}

void MGLVertexArray_Complete(MGLVertexArray * vertex_array) {
	const GLMethods & gl = vertex_array->context->gl;

	PyObject * name;
	MGLAttribute * program_attribute;
	Py_ssize_t pos = 0;

	PyObject * attributes = PyDict_New();

	while (PyDict_Next(vertex_array->program->attributes, &pos, &name, (PyObject **)&program_attribute)) {

		if (program_attribute->array_length > 1) {

			if (program_attribute->rows_length > 1) {

				MGLVertexArrayListAttribute * attrib_list = MGLVertexArrayListAttribute_New();
				attrib_list->vertex_array = vertex_array;
				attrib_list->content = PyTuple_New(program_attribute->array_length);
				attrib_list->location = program_attribute->location;

				for (int i = 0; i < program_attribute->array_length; ++i) {
					MGLVertexArrayListAttribute * matrix = MGLVertexArrayListAttribute_New();
					matrix->vertex_array = vertex_array;
					matrix->content = PyTuple_New(program_attribute->rows_length);
					matrix->location = attrib_list->location + i * program_attribute->rows_length;

					for (int j = 0; j < program_attribute->rows_length; ++j) {
						MGLVertexArrayAttribute * attrib = MGLVertexArrayAttribute_New();
						attrib->vertex_array = vertex_array;
						attrib->location = matrix->location + j;
						attrib->type = program_attribute->type;
						MGLVertexArrayAttribute_Complete(attrib, gl);

						PyTuple_SET_ITEM(matrix->content, j, (PyObject *)attrib);
					}

					PyTuple_SET_ITEM(attrib_list->content, i, (PyObject *)matrix);
				}

				PyDict_SetItem(attributes, name, (PyObject *)attrib_list);

			} else {

				MGLVertexArrayListAttribute * attrib_list = MGLVertexArrayListAttribute_New();
				attrib_list->vertex_array = vertex_array;
				attrib_list->content = PyTuple_New(program_attribute->array_length);
				attrib_list->location = program_attribute->location;

				for (int i = 0; i < program_attribute->array_length; ++i) {
					MGLVertexArrayAttribute * attrib = MGLVertexArrayAttribute_New();
					attrib->vertex_array = vertex_array;
					attrib->location = attrib_list->location + i;
					attrib->type = program_attribute->type;
					MGLVertexArrayAttribute_Complete(attrib, gl);

					PyTuple_SET_ITEM(attrib_list->content, i, (PyObject *)attrib);
				}

				PyDict_SetItem(attributes, name, (PyObject *)attrib_list);

			}

		} else {

			if (program_attribute->rows_length > 1) {
				MGLVertexArrayListAttribute * matrix = MGLVertexArrayListAttribute_New();
				matrix->vertex_array = vertex_array;
				matrix->content = PyTuple_New(program_attribute->rows_length);
				matrix->location = program_attribute->location;

				for (int j = 0; j < program_attribute->rows_length; ++j) {
					MGLVertexArrayAttribute * attrib = MGLVertexArrayAttribute_New();
					attrib->vertex_array = vertex_array;
					attrib->location = matrix->location + j;
					attrib->type = program_attribute->type;
					MGLVertexArrayAttribute_Complete(attrib, gl);

					PyTuple_SET_ITEM(matrix->content, j, (PyObject *)attrib);
				}

				PyDict_SetItem(attributes, name, (PyObject *)matrix);

			} else {

				MGLVertexArrayAttribute * attrib = MGLVertexArrayAttribute_New();
				attrib->vertex_array = vertex_array;
				attrib->location = program_attribute->location;
				attrib->type = program_attribute->type;
				MGLVertexArrayAttribute_Complete(attrib, gl);

				PyDict_SetItem(attributes, name, (PyObject *)attrib);
			}
		}
	}

	vertex_array->attributes = attributes;

	// Subroutines

	gl.GetProgramStageiv(
		vertex_array->program->program_obj,
		GL_VERTEX_SHADER,
		GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS,
		&vertex_array->num_vertex_shader_subroutine_uniform_locations
	);

	gl.GetProgramStageiv(
		vertex_array->program->program_obj,
		GL_FRAGMENT_SHADER,
		GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS,
		&vertex_array->num_fragment_shader_subroutine_uniform_locations
	);

	gl.GetProgramStageiv(
		vertex_array->program->program_obj,
		GL_GEOMETRY_SHADER,
		GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS,
		&vertex_array->num_geometry_shader_subroutine_uniform_locations
	);

	gl.GetProgramStageiv(
		vertex_array->program->program_obj,
		GL_TESS_EVALUATION_SHADER,
		GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS,
		&vertex_array->num_tess_evaluation_shader_subroutine_uniform_locations
	);

	gl.GetProgramStageiv(
		vertex_array->program->program_obj,
		GL_TESS_CONTROL_SHADER,
		GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS,
		&vertex_array->num_tess_control_shader_subroutine_uniform_locations
	);

	vertex_array->num_subroutine_uniform_locations = 0;
	vertex_array->num_subroutine_uniform_locations += vertex_array->num_vertex_shader_subroutine_uniform_locations;
	vertex_array->num_subroutine_uniform_locations += vertex_array->num_fragment_shader_subroutine_uniform_locations;
	vertex_array->num_subroutine_uniform_locations += vertex_array->num_geometry_shader_subroutine_uniform_locations;
	vertex_array->num_subroutine_uniform_locations += vertex_array->num_tess_evaluation_shader_subroutine_uniform_locations;
	vertex_array->num_subroutine_uniform_locations += vertex_array->num_tess_control_shader_subroutine_uniform_locations;

	if (vertex_array->num_subroutine_uniform_locations) {
		vertex_array->subroutine_uniform_locations = new unsigned[vertex_array->num_subroutine_uniform_locations];
	} else {
		vertex_array->subroutine_uniform_locations = 0;
	}
}
