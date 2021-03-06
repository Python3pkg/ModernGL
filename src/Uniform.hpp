#pragma once

#include "Python.hpp"

#include "ProgramMember.hpp"
#include "Program.hpp"

struct MGLUniform : public MGLProgramMember {
	PyObject * name;

	void * value_getter;
	void * value_setter;
	void * gl_value_reader_proc;
	void * gl_value_writer_proc;

	int number;
	int location;
	int type;

	int dimension;
	int element_size;
	int array_length;

	bool matrix;
};

extern PyTypeObject MGLUniform_Type;

MGLUniform * MGLUniform_New();
void MGLUniform_Invalidate(MGLUniform * uniform);
void MGLUniform_Complete(MGLUniform * self, const GLMethods & gl);

typedef void (GLAPI * gl_uniform_reader_proc)(GLuint program, GLint location, void * value);
typedef void (GLAPI * gl_uniform_vector_writer_proc)(GLuint program, GLint location, GLsizei count, const void * value);
typedef void (GLAPI * gl_uniform_matrix_writer_proc)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const void * value);

typedef PyObject * (* MGLUniform_Getter)(MGLUniform * self);
typedef int (* MGLUniform_Setter)(MGLUniform * self, PyObject * value);

PyObject * MGLUniform_invalid_getter(MGLUniform * self);
PyObject * MGLUniform_bool_value_getter(MGLUniform * self);
PyObject * MGLUniform_int_value_getter(MGLUniform * self);
PyObject * MGLUniform_uint_value_getter(MGLUniform * self);
PyObject * MGLUniform_float_value_getter(MGLUniform * self);
PyObject * MGLUniform_double_value_getter(MGLUniform * self);
PyObject * MGLUniform_bvec2_value_getter(MGLUniform * self);
PyObject * MGLUniform_bvec3_value_getter(MGLUniform * self);
PyObject * MGLUniform_bvec4_value_getter(MGLUniform * self);
PyObject * MGLUniform_ivec2_value_getter(MGLUniform * self);
PyObject * MGLUniform_ivec3_value_getter(MGLUniform * self);
PyObject * MGLUniform_ivec4_value_getter(MGLUniform * self);
PyObject * MGLUniform_uvec2_value_getter(MGLUniform * self);
PyObject * MGLUniform_uvec3_value_getter(MGLUniform * self);
PyObject * MGLUniform_uvec4_value_getter(MGLUniform * self);
PyObject * MGLUniform_vec2_value_getter(MGLUniform * self);
PyObject * MGLUniform_vec3_value_getter(MGLUniform * self);
PyObject * MGLUniform_vec4_value_getter(MGLUniform * self);
PyObject * MGLUniform_dvec2_value_getter(MGLUniform * self);
PyObject * MGLUniform_dvec3_value_getter(MGLUniform * self);
PyObject * MGLUniform_dvec4_value_getter(MGLUniform * self);
PyObject * MGLUniform_bool_array_value_getter(MGLUniform * self);
PyObject * MGLUniform_int_array_value_getter(MGLUniform * self);
PyObject * MGLUniform_uint_array_value_getter(MGLUniform * self);
PyObject * MGLUniform_float_array_value_getter(MGLUniform * self);
PyObject * MGLUniform_double_array_value_getter(MGLUniform * self);
PyObject * MGLUniform_bvec2_array_value_getter(MGLUniform * self);
PyObject * MGLUniform_bvec3_array_value_getter(MGLUniform * self);
PyObject * MGLUniform_bvec4_array_value_getter(MGLUniform * self);
PyObject * MGLUniform_ivec2_array_value_getter(MGLUniform * self);
PyObject * MGLUniform_ivec3_array_value_getter(MGLUniform * self);
PyObject * MGLUniform_ivec4_array_value_getter(MGLUniform * self);
PyObject * MGLUniform_uvec2_array_value_getter(MGLUniform * self);
PyObject * MGLUniform_uvec3_array_value_getter(MGLUniform * self);
PyObject * MGLUniform_uvec4_array_value_getter(MGLUniform * self);
PyObject * MGLUniform_vec2_array_value_getter(MGLUniform * self);
PyObject * MGLUniform_vec3_array_value_getter(MGLUniform * self);
PyObject * MGLUniform_vec4_array_value_getter(MGLUniform * self);
PyObject * MGLUniform_dvec2_array_value_getter(MGLUniform * self);
PyObject * MGLUniform_dvec3_array_value_getter(MGLUniform * self);
PyObject * MGLUniform_dvec4_array_value_getter(MGLUniform * self);
PyObject * MGLUniform_sampler_value_getter(MGLUniform * self);
PyObject * MGLUniform_sampler_array_value_getter(MGLUniform * self);
PyObject * MGLUniform_float_matrix_2x2_value_getter(MGLUniform * self);
PyObject * MGLUniform_float_matrix_2x3_value_getter(MGLUniform * self);
PyObject * MGLUniform_float_matrix_2x4_value_getter(MGLUniform * self);
PyObject * MGLUniform_float_matrix_3x2_value_getter(MGLUniform * self);
PyObject * MGLUniform_float_matrix_3x3_value_getter(MGLUniform * self);
PyObject * MGLUniform_float_matrix_3x4_value_getter(MGLUniform * self);
PyObject * MGLUniform_float_matrix_4x2_value_getter(MGLUniform * self);
PyObject * MGLUniform_float_matrix_4x3_value_getter(MGLUniform * self);
PyObject * MGLUniform_float_matrix_4x4_value_getter(MGLUniform * self);
PyObject * MGLUniform_double_matrix_2x2_value_getter(MGLUniform * self);
PyObject * MGLUniform_double_matrix_2x3_value_getter(MGLUniform * self);
PyObject * MGLUniform_double_matrix_2x4_value_getter(MGLUniform * self);
PyObject * MGLUniform_double_matrix_3x2_value_getter(MGLUniform * self);
PyObject * MGLUniform_double_matrix_3x3_value_getter(MGLUniform * self);
PyObject * MGLUniform_double_matrix_3x4_value_getter(MGLUniform * self);
PyObject * MGLUniform_double_matrix_4x2_value_getter(MGLUniform * self);
PyObject * MGLUniform_double_matrix_4x3_value_getter(MGLUniform * self);
PyObject * MGLUniform_double_matrix_4x4_value_getter(MGLUniform * self);
PyObject * MGLUniform_float_matrix_2x2_array_value_getter(MGLUniform * self);
PyObject * MGLUniform_float_matrix_2x3_array_value_getter(MGLUniform * self);
PyObject * MGLUniform_float_matrix_2x4_array_value_getter(MGLUniform * self);
PyObject * MGLUniform_float_matrix_3x2_array_value_getter(MGLUniform * self);
PyObject * MGLUniform_float_matrix_3x3_array_value_getter(MGLUniform * self);
PyObject * MGLUniform_float_matrix_3x4_array_value_getter(MGLUniform * self);
PyObject * MGLUniform_float_matrix_4x2_array_value_getter(MGLUniform * self);
PyObject * MGLUniform_float_matrix_4x3_array_value_getter(MGLUniform * self);
PyObject * MGLUniform_float_matrix_4x4_array_value_getter(MGLUniform * self);
PyObject * MGLUniform_double_matrix_2x2_array_value_getter(MGLUniform * self);
PyObject * MGLUniform_double_matrix_2x3_array_value_getter(MGLUniform * self);
PyObject * MGLUniform_double_matrix_2x4_array_value_getter(MGLUniform * self);
PyObject * MGLUniform_double_matrix_3x2_array_value_getter(MGLUniform * self);
PyObject * MGLUniform_double_matrix_3x3_array_value_getter(MGLUniform * self);
PyObject * MGLUniform_double_matrix_3x4_array_value_getter(MGLUniform * self);
PyObject * MGLUniform_double_matrix_4x2_array_value_getter(MGLUniform * self);
PyObject * MGLUniform_double_matrix_4x3_array_value_getter(MGLUniform * self);
PyObject * MGLUniform_double_matrix_4x4_array_value_getter(MGLUniform * self);

int MGLUniform_invalid_setter(MGLUniform * self, PyObject * value);
int MGLUniform_bool_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_int_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_uint_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_float_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_double_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_bvec2_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_ivec2_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_uvec2_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_vec2_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_dvec2_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_bvec3_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_ivec3_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_uvec3_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_vec3_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_dvec3_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_bvec4_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_ivec4_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_uvec4_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_vec4_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_dvec4_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_bool_array_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_int_array_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_uint_array_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_float_array_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_double_array_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_bvec2_array_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_ivec2_array_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_uvec2_array_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_vec2_array_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_dvec2_array_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_bvec3_array_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_ivec3_array_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_uvec3_array_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_vec3_array_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_dvec3_array_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_bvec4_array_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_ivec4_array_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_uvec4_array_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_vec4_array_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_dvec4_array_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_sampler_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_sampler_array_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_float_matrix_2x2_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_float_matrix_2x3_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_float_matrix_2x4_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_float_matrix_3x2_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_float_matrix_3x3_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_float_matrix_3x4_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_float_matrix_4x2_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_float_matrix_4x3_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_float_matrix_4x4_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_double_matrix_2x2_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_double_matrix_2x3_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_double_matrix_2x4_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_double_matrix_3x2_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_double_matrix_3x3_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_double_matrix_3x4_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_double_matrix_4x2_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_double_matrix_4x3_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_double_matrix_4x4_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_float_matrix_2x2_array_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_float_matrix_2x3_array_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_float_matrix_2x4_array_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_float_matrix_3x2_array_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_float_matrix_3x3_array_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_float_matrix_3x4_array_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_float_matrix_4x2_array_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_float_matrix_4x3_array_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_float_matrix_4x4_array_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_double_matrix_2x2_array_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_double_matrix_2x3_array_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_double_matrix_2x4_array_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_double_matrix_3x2_array_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_double_matrix_3x3_array_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_double_matrix_3x4_array_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_double_matrix_4x2_array_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_double_matrix_4x3_array_value_setter(MGLUniform * self, PyObject * value);
int MGLUniform_double_matrix_4x4_array_value_setter(MGLUniform * self, PyObject * value);
