static const char gVertexShader[] =
    "varying vec4 color;                                                    \n"
    "void main() {                                                          \n"
    "    gl_Position   = gl_ModelViewProjectionMatrix * gl_Vertex;          \n"
    "    vec3 normal   = normalize(gl_NormalMatrix * gl_Normal);            \n"
    "    vec4 ecPos    = gl_ModelViewMatrix * gl_Vertex;                    \n"
    "    color = vec4(1.0,1.0,1.0,1.0);               \n"
    "}                                                                      \n";

static const char gFragmentShader[] =
    "precision mediump float;                  \n"
    "varying mediump vec4 color;               \n"
    "void main() {                             \n"
    "  gl_FragColor = color;                   \n"
    "}                                         \n";
