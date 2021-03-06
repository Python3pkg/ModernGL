'''
    ModernGL context
'''

# pylint: disable=using-constant-test, too-many-public-methods

try:
    from ModernGL import mgl
except ImportError:
    pass

from .common import InvalidObject
from .buffers import Buffer, detect_format
from .programs import ComputeShader, Shader, Program
from .vertex_arrays import VertexArray
from .textures import Texture
from .renderbuffers import Renderbuffer
from .framebuffers import Framebuffer


class Context:
    '''
        Create a :py:class:`Context` using:

        - :py:func:`ModernGL.create_context`
        - :py:func:`ModernGL.create_standalone_context`

        The :py:func:`create_context` must be used when rendering in a window.
        The :py:func:`create_standalone_context` must be used when rendering
        without a window.

        Members:

            - :py:meth:`Context.program`
            - :py:meth:`Context.vertex_shader`
            - :py:meth:`Context.fragment_shader`
            - :py:meth:`Context.geometry_shader`
            - :py:meth:`Context.tess_evaluation_shader`
            - :py:meth:`Context.tess_control_shader`
            - :py:meth:`Context.buffer`
            - :py:meth:`Context.simple_vertex_array`
            - :py:meth:`Context.vertex_array`
            - :py:meth:`Context.texture`
            - :py:meth:`Context.depth_texture`
            - :py:meth:`Context.renderbuffer`
            - :py:meth:`Context.depth_renderbuffer`
            - :py:meth:`Context.framebuffer`
    '''

    def __init__(self):
        self.mglo = None
        raise NotImplementedError()

    def release(self):
        '''
            Release the ModernGL object.
        '''

        self.mglo.release()
        self.__class__ = InvalidObject

    @staticmethod
    def new(obj):
        '''
            For internal use only.
        '''

        res = Context.__new__(Context)
        res.mglo = obj
        return res

    @property
    def line_width(self) -> float:
        '''
            Set the default line width.
        '''

        return self.mglo.line_width

    @line_width.setter
    def line_width(self, value):
        self.mglo.line_width = value

    @property
    def point_size(self) -> float:
        '''
            Set the default point size.
        '''

        return self.mglo.point_size

    @point_size.setter
    def point_size(self, value):
        self.mglo.point_size = value

    @property
    def viewport(self) -> tuple:
        '''
            The viewport.

            Reading this property may force the GPU to sync.
            Use this property to set the viewport only.
        '''

        return self.mglo.viewport

    @viewport.setter
    def viewport(self, value):
        self.mglo.viewport = tuple(value)

    @property
    def default_texture_unit(self) -> int:
        '''
            The default texture unit.
        '''

        return self.mglo.default_texture_unit

    @default_texture_unit.setter
    def default_texture_unit(self, value):
        self.mglo.default_texture_unit = value

    @property
    def max_texture_units(self) -> int:
        '''
            The max texture units.
        '''

        return self.mglo.max_texture_units

    @property
    def default_framebuffer(self) -> Framebuffer:
        '''
            The default framebuffer.
        '''

        return self.mglo.default_framebuffer

    @property
    def vendor(self) -> str:
        '''
            The vendor.

            :type: str
        '''

        return self.mglo.vendor

    @property
    def renderer(self) -> str:
        '''
            The renderer.

            :type: str
        '''

        return self.mglo.renderer

    @property
    def version(self) -> str:
        '''
            The OpenGL version.

            :type: str
        '''

        return self.mglo.version

    def clear(self, red=0, green=0, blue=0, alpha=0, *, viewport=None) -> None:
        '''
            Clear the framebuffer.

            Values must be in ``(0, 255)`` range.
            If the `viewport` is not ``None`` then scrissor test
            will be used to clear the given viewport.

            If the `viewport` is a 2-tuple it will clear the
            ``(0, 0, width, height)`` where ``(width, height)`` is the 2-tuple.

            If the `viewport` is a 4-tuple it will clear the given viewport.

            Args:
                red (int): color component.
                green (int): color component.
                blue (int): color component.
                alpha (int): alpha component.

            Keyword Args:
                viewport (tuple): The viewport.
        '''

        if viewport is None:
            self.mglo.clear(red, green, blue, alpha)
        else:
            self.mglo.clear_viewport(red, green, blue, alpha, tuple(viewport))

    def enable(self, flag) -> None:
        '''
            Enable flags.

            Valid flags are:

                - :py:data:`ModernGL.BLEND`
                - :py:data:`ModernGL.DEPTH_TEST`
                - :py:data:`ModernGL.CULL_FACE`
                - :py:data:`ModernGL.MULTISAMPLE`

            Args:
                flag: The flag to enable.
        '''

        self.mglo.enable(flag.mglo)

    def disable(self, flag) -> None:
        '''
            Disable flags.

            Valid flags are:

                - :py:data:`ModernGL.BLEND`
                - :py:data:`ModernGL.DEPTH_TEST`
                - :py:data:`ModernGL.CULL_FACE`
                - :py:data:`ModernGL.MULTISAMPLE`

            Args:
                flag: The flag to disable.
        '''

        self.mglo.disable(flag.mglo)

    def finish(self) -> None:
        '''
            Wait for all drawing commands to finish.
        '''

        self.mglo.finish()

    def copy_buffer(self, dst, src, size=-1, *, read_offset=0, write_offset=0) -> None:
        '''
            Copy buffer content.

            Args:
                dst (Buffer): Destination buffer.
                src (Buffer): Source buffer.
                size (int): Size to copy.

            Keyword Args:
                read_offset (int): Read offset.
                write_offset (int): Write offset.
        '''

        self.mglo.copy_buffer(dst.mglo, src.mglo, size, read_offset, write_offset)

    def copy_framebuffer(self, dst, src) -> None:
        '''
            Copy framebuffer content.
            Use this method to blit framebuffers.
            Use this method to copy framebuffer content into a texture.
            Use this method to downsample framebuffers, it will allow
            to read the framebuffer's content.
            Use this method to downsample a framebuffer directly to a texture.

            Args:
                dst (Framebuffer or Texture): Destination framebuffer or texture.
                src (Framebuffer): Source framebuffer.
        '''

        self.mglo.copy_framebuffer(dst.mglo, src.mglo)

    def buffer(self, data=None, *, reserve=0, dynamic=False) -> Buffer:
        '''
            Create a :py:class:`Buffer`.

            Args:
                data (bytes): Content of the new buffer.

            Keyword Args:
                reserve (int): The number of bytes to reserve.
                dynamic (bool): Treat buffer as dynamic.

            Returns:
                Buffer: buffer
        '''

        return Buffer.new(self.mglo.buffer(data, reserve, dynamic))

    def texture(self, size, components, data=None, *, samples=0, floats=False) -> Texture:
        '''
            Create a :py:class:`Texture`.

            Args:
                size (tuple): Width, height.
                components (int): The number of components 1, 2, 3 or 4.
                data (bytes): Content of the image.

            Keyword Args:
                floats (bool): Use floating point precision.

            Returns:
                Texture: texture
        '''

        return Texture.new(self.mglo.texture(size, components, data, samples, floats))

    def depth_texture(self, size, data=None, *, samples=0) -> Texture:
        '''
            Create a :py:class:`Texture`.

            Args:
                size: The width and height.
                optional data: The pixels.

            Returns:
                Texture: depth texture
        '''

        return Texture.new(self.mglo.depth_texture(size, data, samples))

    def vertex_array(self, program, content, index_buffer=None) -> VertexArray:
        '''
            Create a :py:class:`VertexArray`.

            Args:
                program (Program): The program used by `render` and `transform`.
                content (list): A list of (buffer, format, attributes).
                index_buffer (Buffer): An index buffer.

            Returns:
                VertexArray: vertex array
        '''

        if index_buffer is not None:
            index_buffer = index_buffer.mglo

        content = tuple((a.mglo, b, tuple(c)) for a, b, c in content)
        return VertexArray.new(self.mglo.vertex_array(program.mglo, content, index_buffer))

    def simple_vertex_array(self, program, buffer, attributes) -> VertexArray:
        '''
            Create a :py:class:`VertexArray`.

            This is an alias for:

                format = detect_format(program, attributes)
                vertex_array(program, [(buffer, format, attributes)])

            Args:
                program (Program): The program used by `render` and `transform`.
                buffer (Buffer): The buffer.
                attributes (list): A list of attribute names.

            Returns:
                VertexArray: vertex array
        '''

        content = [(buffer, detect_format(program, attributes), attributes)]
        return self.vertex_array(program, content, None)

    def program(self, shaders, varyings=()) -> Program:
        '''
            Create a :py:class:`Program` object.
            Only linked programs will be returned.

            For more information please see: :py:class:`Program` and :py:class:`Shader`

            A single shader in the `shaders` parameter is also accepted.
            The varyings are only used when a transform program is created.

            Args:
                shaders (list): A list of `Shader` objects.
                varyings (list): A list of varying names.

            Returns:
                Program: program

            Examples:

                A simple program designed for rendering::

                    >>> my_render_program = ctx.program([
                    ... 	ctx.vertex_shader(\'\'\'
                    ... 		#version 330
                    ...
                    ... 		in vec2 vert;
                    ...
                    ... 		void main() {
                    ... 			gl_Position = vec4(vert, 0.0, 1.0);
                    ... 		}
                    ... 	\'\'\'),
                    ... 	ctx.fragment_shader(\'\'\'
                    ... 		#version 330
                    ...
                    ... 		out vec4 color;
                    ...
                    ... 		void main() {
                    ... 			color = vec4(0.3, 0.5, 1.0, 1.0);
                    ... 		}
                    ... 	\'\'\'),
                    ... ])

                A simple program designed for transforming::

                    >>> my_vertex_shader = ctx.vertex_shader(\'\'\'
                    ...     #version 330
                    ...
                    ...     in vec4 vert;
                    ...     out float vert_length;
                    ...
                    ...     void main() {
                    ...         vert_length = length(vert);
                    ...     }
                    ... \'\'\')

                    >>> my_transform_program = ctx.program(my_vertex_shader, ['vert_length'])
        '''

        if isinstance(shaders, Shader):
            shaders = (shaders.mglo,)

        else:
            shaders = tuple(x.mglo for x in shaders)

        return Program.new(self.mglo.program(shaders, tuple(varyings)))

    def vertex_shader(self, source) -> Shader:
        '''
            The Vertex Shader is the programmable Shader stage in the rendering pipeline
            that handles the processing of individual vertices.

            Vertex shaders are fed Vertex Attribute data, as specified from a vertex array
            object by a drawing command. A vertex shader receives a single vertex from the
            vertex stream and generates a single vertex to the output vertex stream.

            Args:
                source (str): The source code in GLSL.

            Returns:
                Shader: vertex shader

            Examples:

                Create a simple vertex shader::

                    >>> my_vertex_shader = ctx.vertex_shader(\'\'\'
                    ...     #version 330
                    ...
                    ...     in vec2 vert;
                    ...
                    ...     void main() {
                    ...         gl_Position = vec4(vert, 0.0, 1.0);
                    ...     }
                    ... \'\'\')
        '''

        return Shader.new(self.mglo.vertex_shader(source))

    def fragment_shader(self, source) -> Shader:
        '''
            A Fragment Shader is the Shader stage that will process a Fragment generated by
            the Rasterization into a set of colors and a single depth value.

            Args:
                source (str): The source code in GLSL.

            Returns:
                Shader: fragment shader

            Examples:

                Create a simple fragment shader::

                    >>> my_fragment_shader = ctx.fragment_shader(\'\'\'
                    ...     #version 330
                    ...
                    ...     out vec4 color;
                    ...
                    ...     void main() {
                    ...         color = vec4(0.3, 0.5, 1.0, 1.0);
                    ...     }
                    ... \'\'\')
        '''

        return Shader.new(self.mglo.fragment_shader(source))

    def geometry_shader(self, source) -> Shader:
        '''
            Create a :py:class:`Shader`.

            Args:
                source (str): The source code in GLSL.

            Returns:
                Shader: geometry shader
        '''

        return Shader.new(self.mglo.geometry_shader(source))

    def tess_evaluation_shader(self, source) -> Shader:
        '''
            Create a :py:class:`Shader`.

            Args:
                source (str): The source code in GLSL.

            Returns:
                Shader: tesselation evaluation shader
        '''

        return Shader.new(self.mglo.tess_evaluation_shader(source))

    def tess_control_shader(self, source) -> Shader:
        '''
            Create a :py:class:`Shader`.

            Args:
                source (str): The source code in GLSL.

            Returns:
                Shader: tesselation control shader
        '''

        return Shader.new(self.mglo.tess_control_shader(source))

    def framebuffer(self, color_attachments, depth_attachment) -> Framebuffer:
        '''
            Create a :py:class:`Framebuffer`.

            Args:
                color_attachments (list): A list of `Texture` or `Renderbuffer` objects.
                depth_attachment (Renderbuffer or Texture): A `Texture` or `Renderbuffer` object.

            Returns:
                Framebuffer: framebuffer
        '''

        if isinstance(color_attachments, (Texture, Renderbuffer)):
            color_attachments = (color_attachments.mglo,)

        else:
            color_attachments = tuple(x.mglo for x in color_attachments)

        return Framebuffer.new(self.mglo.framebuffer(color_attachments, depth_attachment.mglo))

    def renderbuffer(self, size, components=4, *, samples=0, floats=True) -> Renderbuffer:
        '''
            Create a :py:class:`Renderbuffer`.

            Args:
                size (tuple): The width and height.
                components (int): The number of components 1, 2, 3 or 4.

            Keyword Args:
                samples: The number of samples. Value `0` means no multisample format.
                floats: Use floating point precision.

            Returns:
                Renderbuffer: renderbuffer
        '''

        return Renderbuffer.new(self.mglo.renderbuffer(size, components, samples, floats))

    def depth_renderbuffer(self, size, *, samples=0) -> Renderbuffer:
        '''
            Create a :py:class:`Renderbuffer`.

            Args:
                size (tuple): The width and height.

            Keyword Args:
                samples: The number of samples. Value `0` means no multisample format.

            Returns:
                Renderbuffer: depth renderbuffer
        '''

        return Renderbuffer.new(self.mglo.depth_renderbuffer(size, samples))

    def compute_shader(self, source) -> ComputeShader:
        '''
            ``NYI``

            Create a :py:class:`ComputeShader`.

            Args:
                source (str): The source of the compute shader.

            Returns:
                ComputeShader: compute shader program
        '''

        return ComputeShader.new(self.mglo.compute_shader(source))


if False:
    def _create_context() -> Context:
        return Context()

    def _create_standalone_context(*args) -> Context:
        return Context(*args)

    mgl.create_context = _create_context
    mgl.create_standalone_context = _create_standalone_context


def create_context(require=None) -> Context:
    '''
        Create a ModernGL context by loading OpenGL functions from an existing OpenGL context.
        An OpenGL context must exists. If rendering is done without a window please use the
        :py:func:`create_standalone_context` instead.

        Keyword Arguments:
            require (Version): OpenGL version.

        Returns:
            Context: context
    '''

    ctx = Context.new(mgl.create_context())

    if require is not None and ctx.version < require:
        raise Exception('The version required is not provided')

    return ctx


def create_standalone_context(size=(256, 256), require=None) -> Context:
    '''
        Create a standalone ModernGL context.
        This method will create a hidden window with the
        initial size given in the parameters. This will
        set the  initial viewport as well.

        It is reccommanded to use a separate framebuffer when rendering.

        The size is not really important for the default framebuffer.
        It is only useful to get a viewport with a visible size.
        Size ``(1, 1)`` is great to save memory, however makes harder to
        detect when the viewport was forgotten to set.

        Keyword Arguments:
            size (tuple): Initial framebuffer size.
            require (Version): OpenGL version.

        Returns:
            Context: context
    '''

    ctx = Context.new(mgl.create_standalone_context(*size))

    if require is not None and ctx.version < require:
        raise Exception('The version required is not provided')

    return ctx


class ContextManager:
    '''
        ContextManager
    '''

    cache = {}

    @staticmethod
    def create_context(name='primary', standalone=False) -> Context:
        '''
            Create a named OpenGL context.

            This is only useful to solve the problem of importing
            ModernGL from submodules, that has access to the same context.

            The name `primary` is the default name.

            Returns:
                Context: context
        '''

        ctx = ContextManager.cache.get(name)

        if not ctx:
            if standalone:
                ctx = create_standalone_context()
            else:
                ctx = create_context()

        ContextManager.cache[name] = ctx

        return ctx

    @staticmethod
    def release_context(name) -> None:
        '''
            Release a named context.
            Fails silently.
        '''

        ctx = ContextManager.cache.get(name)

        if not ctx:
            return

        ctx.release()

        del ContextManager.cache[name]
