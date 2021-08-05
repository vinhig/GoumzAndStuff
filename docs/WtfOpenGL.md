# Why OpenGL?

A list of weird OpenGL characteristics discovered while developing this engine :

* On OpenGL 33, it's okay to `glBlitFramebuffer` two framebuffers with textures that have different internal formats. But in OpenGL ES 3.2 it's not.
* Not very weird, but kinda annoying when your forget it: make sure to always call `glDrawBuffers` with your attachments after creating a framebuffer. Or else only the default attachment will be used (only one color buffer in that case).
    * Nothing to do on the client side; The engine take care of that.
* The same texture creation path doesn't produce the same texture with OpenGL 3.3 and OpenGL ES 3.2... The internal format somewhat changed. I had to put some `if` there and there... 
* RenderDoc crashes if you delete an object that isn't initialised, but the application doesn't if you don't attach the debugger :
    * `unsigned int framebuffer; /*not initialised*/ glDeleteFramebuffers(1, &framebuffer);`
* Some mobile drivers doesn't want their shaders last line to be a comment. Wtf ????