//uniform sampler2D qt_Texture0;
//varying highp vec4 qt_TexCoord0;
uniform highp vec4 color;
void main(void)
{
    gl_FragColor = color;
}
