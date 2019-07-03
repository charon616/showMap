// #version 150

// uniform sampler2DRect tex0;     // ソースのテクスチャ
// //uniform sampler2DRect tex_show;
// uniform float threshold;        // 閾値
// uniform vec3 chromaKeyColor;    // キーの色
// in vec2 texCoordVarying;
// out vec4 outputColor;

// void main()
// {
//     // テクスチャーの色を取得
//     vec4 texel0 = texture(tex0, texCoordVarying);
//     //vec4 texel_show = texture2DRect(tex_show, texCoordVarying);
//     // キーの色との差分を計算
//     float diff = length(chromaKeyColor - texel0.rgb);
//     if(diff < threshold){
//         // もしキーの色より差分が少なかったら描画しない
//         discard;
//     }else{
//         // キーの色より差分が多かったら、そのまま描画
//         outputColor = texel0;
//       //gl_FragColor = texel0 * texel0;
//         //gl_FragColor = texel_show;
//     }
// }

uniform vec2 resolution;
uniform sampler2DRect tex;
uniform sampler2DRect tex_show;
uniform float time;
uniform float threshold;    // 閾値
varying vec2 vTexCoord;

void main() {
    vec4 samplerColor = texture2DRect(tex, vTexCoord);
    vec4 texel1 = texture2DRect(tex_show, vTexCoord);
    vec2 p = (gl_FragCoord.xy * 2.0 - resolution) / resolution;
    float t = (sin(time) + 1.0) * 0.5;
    float diff = length((0.0, 0.0, 0.0) - samplerColor.rgb);
    if(diff < threshold){
        // もしキーの色より差分が少なかったら描画しない
        discard;
    }else{
	    //vec2 tvec = p * 0.5 + vec2(t) * 0.5;
	    //gl_FragColor = vec4(samplerColor.r + tvec.x, samplerColor.g, samplerColor.b + tvec.y, 1.0);
	    //gl_FragColor = vec4(samplerColor.r, samplerColor.g, samplerColor.b, 1.0);
	    gl_FragColor = vec4(texel1.r, texel1.g, texel1.b, 1.0);
	}
}