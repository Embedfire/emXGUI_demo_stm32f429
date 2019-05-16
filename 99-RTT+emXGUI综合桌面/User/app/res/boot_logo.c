/* 要修改开机界面logo，
 * 使用bin2c软件转换png文件得到的数组内容，替换即可
 * 本示例的png图片分辨率为220*119
*/
const char bootlogo[] = {137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,
0,0,0,220,0,0,0,119,8,6,0,0,0,104,129,46,
172,0,0,0,1,115,82,71,66,0,174,206,28,233,0,0,
0,4,103,65,77,65,0,0,177,143,11,252,97,5,0,0,
0,9,112,72,89,115,0,0,18,116,0,0,18,116,1,222,
102,31,120,0,0,38,99,73,68,65,84,120,94,237,93,9,
152,29,69,181,30,81,31,130,250,144,199,243,185,241,34,40,
136,34,100,230,86,223,201,204,220,238,59,131,66,52,34,32,
42,65,64,17,55,68,101,19,120,178,61,48,70,64,150,71,
4,9,251,22,118,72,88,68,100,139,4,99,200,50,51,119,
153,9,48,4,217,247,69,64,8,178,5,72,50,239,255,171,
79,247,244,237,219,119,155,185,219,76,234,255,190,243,221,219,
85,167,182,83,231,212,214,213,85,45,6,6,6,6,6,6,
6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
6,6,6,6,6,6,6,6,235,36,134,91,90,222,211,223,
21,235,78,219,214,204,140,173,102,25,50,180,46,80,218,86,
199,226,183,147,250,47,166,80,123,100,19,177,79,34,225,249,
105,71,221,156,117,98,63,204,38,226,187,24,50,180,46,80,
58,161,126,2,131,187,3,186,255,167,1,167,237,163,98,18,
181,195,194,158,173,63,132,94,109,17,19,158,209,210,178,158,
56,27,24,172,51,64,239,182,30,12,238,160,140,163,254,114,
235,180,45,214,23,231,218,0,214,189,63,12,238,172,186,118,
169,6,6,77,6,118,54,176,131,203,51,9,245,93,113,170,
62,104,100,41,91,221,146,78,42,37,78,6,6,235,44,96,
108,201,172,99,205,147,199,234,99,97,79,207,251,210,142,181,
44,211,99,253,167,56,25,24,172,179,184,123,202,148,77,49,
180,156,47,143,213,71,198,178,222,159,182,85,170,111,202,148,
127,23,39,3,131,117,22,203,58,59,255,35,99,91,183,201,
99,245,97,12,206,192,96,4,198,224,12,12,234,8,99,112,
6,6,117,132,49,56,3,131,58,98,194,25,28,10,180,1,
211,148,71,3,131,166,194,132,51,184,225,158,158,247,165,156,
248,14,242,104,96,208,84,152,144,67,74,164,119,216,61,206,
182,27,203,163,129,65,211,96,66,26,92,182,59,182,75,218,
177,14,151,71,3,131,166,193,132,52,184,101,157,173,159,74,
59,234,137,33,20,78,156,12,38,24,184,47,145,196,173,131,
30,137,87,93,193,53,3,52,238,123,102,28,117,110,198,177,
46,97,67,159,78,168,207,138,119,30,38,164,193,101,118,178,
54,76,57,214,227,40,252,161,226,100,48,129,176,188,107,242,
127,165,108,149,77,219,214,3,168,227,52,104,25,116,108,41,
232,102,184,205,73,117,197,99,194,90,83,12,38,90,219,144,
102,22,141,251,5,233,164,250,122,202,105,235,161,206,225,249,
94,184,31,54,60,99,70,222,151,49,19,210,224,216,218,101,
108,213,143,86,231,239,203,167,78,254,160,56,55,28,15,78,
219,98,253,121,211,167,191,87,30,107,2,202,91,254,234,125,
172,36,121,172,26,130,105,52,2,243,182,222,250,223,80,191,
143,160,71,25,206,35,91,189,155,177,167,116,10,107,205,48,
212,211,254,113,164,183,188,223,137,77,235,79,198,186,83,137,
248,46,41,59,182,115,166,203,250,60,191,121,203,218,214,157,
208,251,125,132,221,199,132,52,56,2,5,254,51,4,178,150,
66,16,167,134,3,13,192,133,104,129,87,176,49,128,76,230,
35,127,243,50,78,252,92,228,245,20,248,253,26,238,7,151,
75,8,127,44,194,28,135,22,245,116,84,224,197,248,127,11,
254,103,240,123,146,36,215,130,180,246,67,107,123,191,219,11,
168,191,226,247,6,244,12,87,129,231,156,148,163,102,187,225,
213,111,211,78,236,208,168,52,224,255,107,225,57,17,252,28,
50,205,67,28,119,33,222,5,181,48,228,74,128,124,220,169,
13,44,159,174,71,131,91,243,111,46,41,151,129,164,117,36,
255,99,52,117,73,22,134,71,210,242,236,178,118,27,236,232,
216,140,117,61,132,198,65,7,16,76,88,131,131,194,220,232,
86,128,98,5,52,197,119,120,168,144,51,67,202,81,117,130,
34,250,195,104,252,63,60,138,103,172,4,165,122,184,209,189,
28,148,25,141,76,126,222,6,34,122,149,114,192,145,7,122,
169,173,228,177,40,134,193,11,217,46,90,214,19,219,130,207,
104,176,206,28,158,225,26,57,140,201,161,209,233,255,142,117,
83,170,171,173,157,255,61,76,120,131,67,197,188,206,49,191,
56,55,20,153,132,250,85,80,57,106,65,3,221,214,142,146,
220,132,54,56,244,212,199,71,229,45,139,225,157,176,84,12,
24,220,183,49,23,251,132,60,22,4,140,102,3,232,87,127,
102,7,107,35,62,195,224,110,128,158,157,5,67,90,4,93,
255,67,63,134,155,116,199,232,101,118,42,17,219,133,255,61,
76,88,131,131,82,252,213,175,4,39,246,61,113,110,40,250,
209,250,6,149,3,180,22,249,124,39,76,168,204,119,131,124,
48,156,72,62,151,172,181,62,175,109,173,238,79,180,199,37,
185,9,109,112,144,229,97,81,121,203,38,98,126,249,43,5,
123,56,140,136,102,151,26,17,177,55,131,78,223,129,185,218,
214,124,246,122,184,187,187,213,182,168,187,89,222,112,59,149,
80,127,73,195,141,255,61,76,72,131,227,184,25,45,206,125,
94,37,32,253,107,196,171,161,232,75,88,223,8,42,7,242,
245,124,175,163,58,88,41,57,228,180,237,6,191,213,1,190,
108,30,143,71,142,122,194,231,115,172,85,203,157,246,207,73,
114,104,97,219,247,133,255,98,184,207,69,28,103,67,38,167,
64,33,142,66,133,31,9,183,67,121,198,76,33,130,226,157,
20,204,67,144,154,193,224,82,118,252,71,81,121,203,58,237,
219,11,75,197,224,2,27,202,118,127,186,51,215,72,162,0,
35,59,36,235,88,167,209,56,241,255,116,111,72,153,114,226,
123,32,142,131,82,221,241,118,200,122,48,124,134,207,132,52,
184,254,237,219,55,129,114,189,230,85,2,210,127,110,94,75,
75,77,87,7,203,65,182,43,214,29,84,14,228,235,41,30,
176,36,222,62,6,236,182,86,248,141,244,114,182,90,34,94,
121,64,57,31,242,227,115,212,27,168,204,73,226,53,106,80,
126,48,184,148,159,190,23,191,109,173,2,93,51,224,196,123,
26,61,47,238,79,168,239,134,243,71,130,193,77,19,150,81,
1,114,191,23,101,60,95,30,11,130,250,140,122,89,148,78,
90,63,243,134,144,4,231,130,8,63,21,117,145,205,36,213,
87,197,217,199,132,52,184,180,221,186,93,184,34,6,186,219,
182,20,239,134,129,231,89,4,243,212,140,6,167,71,7,142,
117,189,159,182,79,106,40,213,21,79,132,91,236,70,129,203,
240,249,121,28,155,193,177,17,129,172,105,112,175,176,209,17,
231,130,224,209,143,224,191,17,242,226,202,237,17,248,61,16,
114,186,136,113,100,237,248,206,81,141,210,4,53,184,216,41,
225,138,24,236,110,223,93,188,27,134,102,55,56,42,136,251,
138,98,36,143,58,94,12,105,203,81,192,74,1,221,216,144,
11,15,156,243,84,218,99,214,194,224,152,23,196,241,12,227,
129,241,236,41,206,69,161,87,55,187,227,49,200,254,231,41,
91,29,12,35,220,101,40,162,78,61,76,56,131,27,70,122,
80,208,188,151,162,80,204,153,194,210,48,52,218,224,116,11,
94,228,48,39,119,206,23,88,132,97,156,182,245,66,182,211,
93,254,174,54,80,174,131,117,58,182,181,18,243,161,94,60,
207,26,72,198,19,229,188,227,171,133,193,241,5,246,72,249,
213,69,226,92,85,76,56,131,131,160,118,10,87,2,9,189,
222,28,97,105,24,32,104,39,55,79,245,51,56,182,196,232,
189,14,128,255,203,25,59,62,43,252,53,5,63,105,66,248,
55,253,52,221,248,222,204,58,177,81,47,66,148,2,234,106,
70,48,61,55,77,107,45,202,84,114,145,171,218,6,55,111,
122,203,123,81,222,235,188,120,240,63,5,231,170,207,83,39,
148,193,177,101,68,133,245,6,43,96,132,212,45,194,214,48,
44,237,137,111,19,204,19,134,32,207,246,98,110,201,205,214,
65,130,194,77,13,25,92,42,204,227,17,120,31,243,248,10,
25,156,59,47,83,167,34,206,145,149,79,71,61,12,89,237,
198,253,126,217,238,216,23,144,198,115,158,159,248,191,195,149,
64,4,175,217,226,8,122,181,200,141,0,112,47,217,56,86,
219,224,32,155,189,66,242,121,162,22,243,213,9,101,112,72,
103,159,240,144,104,68,128,86,175,176,53,12,189,84,236,220,
60,33,175,234,95,168,220,92,178,173,215,131,124,48,134,213,
121,60,66,240,95,227,241,225,57,207,224,230,79,157,252,65,
248,113,75,86,158,92,168,96,8,115,29,104,40,199,221,205,
215,113,181,94,32,65,26,126,143,146,147,126,151,250,186,176,
20,68,53,13,174,95,143,138,180,44,71,226,178,213,147,149,
206,43,203,193,132,49,184,190,228,228,205,161,168,47,228,8,
45,64,80,162,180,176,54,12,97,131,171,54,69,25,156,187,
76,173,27,162,199,163,194,68,17,122,222,107,89,111,18,69,
205,0,37,239,15,167,141,188,190,85,142,174,20,52,56,59,
246,45,97,41,9,26,84,58,161,126,14,217,188,29,142,7,
249,232,3,139,49,184,40,48,110,40,219,226,176,208,130,4,
99,188,83,216,27,134,70,24,156,135,37,137,196,135,49,143,
61,1,114,240,223,79,70,17,252,159,170,199,13,47,90,217,
109,245,98,126,250,106,1,188,75,42,122,225,30,174,188,93,
69,122,250,145,180,32,15,229,143,16,130,196,151,217,194,154,
131,224,59,183,209,96,220,27,220,99,61,61,31,128,128,230,
133,5,150,71,104,181,37,72,195,144,63,164,212,91,179,174,
128,146,95,28,36,248,205,67,126,3,115,56,107,101,152,39,
64,129,94,93,189,185,60,57,101,115,73,46,18,220,69,129,
48,127,27,9,19,34,219,194,48,211,186,34,149,140,255,183,
4,169,9,220,235,203,242,123,150,140,29,63,94,88,138,162,
144,193,65,110,251,11,75,65,80,39,83,73,245,123,240,71,
26,27,101,31,222,116,236,33,131,112,156,59,203,99,197,24,
215,6,183,36,177,213,135,161,28,115,35,133,22,34,12,147,
126,47,193,26,134,252,30,78,189,26,117,246,74,182,43,246,
105,26,79,128,239,239,226,149,7,148,223,95,36,210,6,220,
93,122,91,18,191,203,67,184,195,117,143,232,167,145,75,168,
179,103,97,16,63,70,79,84,147,121,92,95,82,125,25,121,
200,159,87,38,173,111,8,75,81,20,52,56,71,253,90,88,
34,193,242,160,220,167,70,165,237,147,29,59,175,80,185,185,
157,11,6,121,134,60,86,140,113,107,112,220,213,13,193,21,
29,70,6,105,32,169,126,34,65,27,134,102,49,56,193,123,
80,241,252,148,228,225,145,116,70,136,113,101,19,214,33,28,
250,9,127,85,1,165,253,101,94,186,232,89,6,59,59,203,
234,61,50,201,246,2,91,187,172,51,133,37,18,41,39,182,
119,161,97,36,9,229,190,18,58,187,161,176,231,33,147,140,
159,193,81,69,177,151,219,197,48,46,13,110,48,209,222,86,
72,81,10,209,242,174,248,54,18,188,97,168,167,193,113,133,
177,28,99,97,195,149,114,212,194,145,180,16,143,109,189,130,
223,93,107,101,108,4,242,157,63,50,137,248,96,179,16,144,
199,3,242,194,131,48,79,253,179,176,228,129,178,134,44,95,
138,10,167,201,86,75,104,108,60,46,161,183,163,117,51,9,
150,3,240,233,21,223,236,40,55,73,143,43,131,163,2,112,
200,1,97,191,156,39,172,34,4,69,124,186,150,202,83,46,
234,105,112,144,209,49,52,36,221,98,59,106,54,135,212,168,
135,99,225,118,116,152,160,104,199,67,9,86,186,113,240,43,
121,117,109,20,95,144,16,39,191,38,248,3,226,215,31,91,
86,2,30,145,128,112,254,87,14,1,186,68,88,74,2,229,
155,25,17,158,180,156,58,39,108,57,200,58,177,3,35,248,
53,161,220,107,184,217,152,27,17,80,174,7,32,147,188,99,
26,180,254,241,139,125,240,163,39,29,213,169,112,227,198,224,
248,249,3,132,192,79,255,223,10,11,171,52,169,217,18,77,
89,224,97,178,242,183,170,168,181,193,65,54,171,179,142,178,
232,158,178,227,92,20,144,240,181,164,120,209,57,83,20,122,
157,216,100,24,237,59,249,113,169,125,133,165,36,144,238,133,
249,225,65,104,140,185,34,43,108,57,64,252,183,68,134,1,
193,144,94,129,174,110,4,158,157,216,232,128,242,14,160,114,
23,156,220,197,172,148,19,175,72,167,60,140,11,131,227,48,
3,202,196,22,58,242,251,172,98,196,48,158,18,150,11,182,
94,200,119,193,113,252,104,81,115,131,3,65,113,182,211,238,
250,204,147,17,247,90,16,210,126,187,223,110,255,162,206,72,
5,72,37,163,231,111,189,29,177,47,8,75,73,64,105,11,
174,180,246,57,83,244,135,161,97,64,38,15,70,241,147,32,
183,151,217,187,161,33,208,219,205,192,251,64,80,103,97,40,
27,100,109,117,179,199,159,74,168,75,197,171,34,52,189,193,
45,228,178,127,210,186,218,43,104,165,132,161,203,252,225,233,
149,157,148,5,69,154,59,218,33,67,49,112,169,57,55,111,
92,22,87,23,65,62,103,135,232,114,42,160,207,167,191,67,
83,247,68,82,104,165,49,155,136,125,135,105,33,204,49,65,
247,26,81,170,210,161,58,249,81,182,59,194,113,65,22,15,
81,169,133,173,40,22,246,124,250,3,224,47,248,34,63,235,
196,35,223,197,65,214,255,132,204,94,68,250,121,163,36,52,
202,239,64,118,113,196,251,191,158,27,254,15,98,152,249,75,
132,57,12,97,251,241,236,175,108,66,238,167,74,180,21,161,
169,13,142,159,75,160,197,249,139,87,200,74,9,233,174,130,
96,58,36,186,178,1,193,242,11,233,231,6,123,90,63,34,
78,85,1,140,96,106,84,62,171,73,94,67,65,131,3,173,
65,249,223,65,89,222,128,146,61,133,95,24,168,213,11,247,
59,161,64,55,194,237,90,132,201,221,210,228,88,79,233,242,
7,136,124,136,39,208,227,186,132,180,42,62,247,211,237,189,
243,210,100,93,93,38,44,37,209,219,211,186,89,184,161,9,
82,214,182,206,18,214,28,100,18,234,104,190,183,197,112,240,
51,224,91,22,21,174,159,70,7,189,9,251,133,9,50,252,
177,68,91,17,154,214,224,250,219,219,55,41,54,108,40,131,
214,242,219,174,209,44,150,32,191,60,194,14,66,109,27,149,
80,11,161,208,87,202,213,36,24,200,21,76,139,31,220,102,
49,87,98,5,235,196,35,192,209,3,20,39,103,152,69,99,
20,111,31,139,109,107,18,100,146,51,156,231,115,111,71,71,
228,74,94,49,164,19,209,11,23,48,130,189,133,165,36,6,
147,234,235,81,113,120,132,188,221,87,170,222,239,114,218,62,
10,190,108,110,56,235,45,46,156,224,247,8,52,50,35,27,
15,66,68,99,47,181,193,160,16,154,210,224,22,187,203,183,
57,75,213,149,18,132,182,96,180,239,74,160,180,25,198,129,
22,252,118,113,170,10,16,239,161,126,30,49,172,113,91,105,
245,18,228,147,75,28,250,228,12,95,184,35,34,159,15,110,
224,99,239,101,249,45,50,220,31,44,119,105,189,128,193,45,
18,111,31,112,219,47,200,163,249,28,181,76,188,203,134,232,
66,95,68,92,111,176,215,17,182,146,72,217,241,147,243,227,
200,145,215,218,116,145,227,198,61,240,149,8,100,24,30,65,
173,228,103,76,200,211,65,144,235,243,33,63,77,40,195,5,
18,69,197,104,58,131,67,134,120,86,251,13,81,5,45,151,
160,32,183,143,101,63,32,226,208,130,70,190,95,44,246,193,
102,165,128,160,29,190,227,97,207,211,135,22,18,207,147,152,
79,182,182,65,90,2,101,65,218,129,61,143,234,105,242,134,
249,120,252,31,135,104,84,214,101,60,80,136,67,214,164,250,
65,185,67,225,114,13,14,115,162,252,97,61,230,54,226,93,
54,250,236,41,157,40,87,196,194,151,74,151,251,101,130,222,
3,25,50,90,228,249,109,184,221,159,227,150,176,14,145,32,
69,161,245,141,199,35,184,239,30,71,194,235,57,162,186,21,
255,115,231,138,118,124,201,88,166,26,77,101,112,50,161,158,
149,83,192,202,233,26,10,81,162,172,24,236,93,209,186,121,
75,214,107,251,187,218,71,125,206,225,104,177,16,21,138,60,
140,204,115,108,245,36,228,88,245,85,211,114,12,142,123,42,
225,22,30,78,174,25,205,87,224,60,201,138,202,141,30,228,
4,148,137,39,64,15,225,151,123,55,127,39,44,37,193,198,
5,233,231,44,122,184,198,162,78,10,185,85,244,117,8,203,
137,56,142,67,88,126,208,155,191,229,204,177,158,65,156,51,
239,47,240,202,161,92,52,149,193,165,187,218,118,227,112,32,
92,216,114,137,47,108,135,166,143,12,167,6,58,218,182,172,
116,14,7,5,232,12,230,129,67,11,241,170,27,154,201,224,
240,156,183,218,201,250,172,198,41,104,92,61,166,1,65,55,
54,21,167,146,200,36,227,121,175,20,144,159,190,129,240,130,
20,230,96,24,77,40,9,86,54,248,14,150,31,5,35,142,
93,97,128,251,34,127,123,12,116,181,181,83,86,194,50,38,
52,141,193,113,120,4,190,200,49,115,153,148,10,190,240,236,
183,91,191,8,195,169,248,60,74,84,212,254,193,120,17,71,
209,189,121,181,64,179,24,220,131,211,166,173,15,165,123,52,
232,175,121,146,234,88,97,169,43,56,156,68,126,242,142,239,
131,124,102,45,117,245,39,119,7,82,66,93,40,65,155,6,
77,99,112,168,232,179,114,132,85,1,65,57,223,8,182,102,
203,39,243,64,79,139,135,210,92,45,78,101,3,21,154,243,
21,50,242,254,71,241,26,51,56,246,231,156,141,7,142,162,
231,45,56,103,185,99,7,107,163,209,24,28,23,75,184,186,
91,110,175,94,202,224,220,111,232,172,253,64,231,35,15,188,
141,232,121,252,142,170,231,168,6,178,221,237,93,200,99,206,
198,99,142,70,56,47,214,211,145,188,5,16,245,106,57,139,
39,245,68,83,24,28,133,2,1,229,189,155,41,159,212,57,
65,37,131,130,28,65,119,40,237,149,226,84,22,152,71,196,
245,143,80,220,11,197,123,204,64,92,188,141,230,37,26,16,
100,242,0,242,151,70,94,23,208,168,81,9,23,227,247,2,
18,120,46,196,115,96,229,209,122,29,52,199,243,247,9,229,
195,239,31,241,203,215,24,105,196,251,8,248,238,43,247,138,
174,114,134,148,30,40,95,206,111,121,254,9,123,26,113,174,
43,178,124,39,24,200,43,41,101,91,43,189,242,34,239,121,
171,169,144,229,57,240,170,248,213,80,173,208,20,6,7,65,
254,46,95,80,101,211,42,126,61,32,81,181,244,118,116,124,
12,5,210,67,11,40,226,173,226,92,22,160,176,187,7,231,
111,110,28,86,70,188,199,12,196,127,84,48,238,90,16,242,
251,76,185,6,119,158,174,155,145,35,225,117,248,2,6,215,
104,112,83,54,228,151,191,194,105,91,254,11,243,187,123,166,
108,10,158,87,131,254,208,189,55,42,221,218,87,75,52,220,
224,144,129,13,96,24,21,125,106,19,162,33,30,113,38,209,
241,146,135,192,30,66,53,196,244,197,171,40,216,106,67,89,
239,10,196,171,9,110,85,59,11,165,46,6,199,247,115,86,
249,175,50,144,167,129,220,240,214,93,226,213,52,96,239,154,
178,11,108,60,78,168,164,176,105,100,236,248,85,97,30,232,
215,98,246,230,194,210,80,52,220,224,244,184,220,46,240,169,
123,25,4,5,241,91,56,190,203,65,92,254,36,31,130,126,
163,220,163,2,6,28,139,23,104,228,229,3,241,87,237,229,
119,125,12,206,122,153,189,188,36,89,18,97,131,131,252,238,
19,175,166,65,54,25,251,54,242,153,215,187,161,190,250,134,
67,251,100,193,215,137,122,143,250,18,97,70,185,115,219,90,
162,225,6,151,73,198,199,116,103,26,132,123,162,68,213,146,
234,138,111,147,87,49,182,58,88,188,11,130,219,116,16,79,
212,247,89,140,191,162,121,96,49,32,47,187,195,32,46,119,
191,77,179,142,97,222,250,19,234,7,89,59,254,45,30,213,
22,36,40,72,96,78,139,201,191,173,246,10,243,144,220,239,
3,213,62,124,17,157,226,55,106,142,117,17,43,85,146,44,
9,228,161,169,13,142,135,246,32,143,249,39,105,99,232,207,
99,22,132,205,7,141,10,242,240,119,245,143,240,243,156,205,
198,223,134,219,120,131,115,55,208,230,8,167,18,226,75,84,
137,138,59,34,246,136,224,121,166,216,74,21,95,224,230,41,
93,128,96,24,126,252,245,4,140,236,159,35,121,80,47,213,
234,36,173,102,54,56,173,59,17,11,37,36,212,203,162,66,
91,216,56,103,139,234,229,216,251,115,115,178,176,53,4,13,
53,56,14,7,32,136,229,97,193,84,66,168,16,255,148,94,
252,63,36,154,7,115,196,164,250,234,188,192,240,67,239,44,
224,61,105,17,71,181,5,9,113,150,117,169,67,181,97,12,
78,95,44,194,213,230,252,233,134,173,222,202,38,98,93,194,
23,9,240,156,147,23,78,135,181,158,170,224,220,151,170,163,
161,6,183,176,181,245,35,16,140,62,98,155,67,4,252,127,
87,255,134,133,84,148,212,0,162,210,99,115,94,70,17,205,
163,105,13,10,250,2,226,95,14,3,124,26,121,42,184,27,
220,35,240,190,157,233,178,62,207,184,235,141,117,221,224,80,
230,189,162,122,41,18,111,71,18,182,130,224,59,79,148,37,
239,165,189,14,143,81,15,239,111,16,214,186,162,161,6,55,
132,241,57,132,250,6,186,250,101,252,228,130,195,187,126,39,
54,13,202,182,176,92,195,67,216,215,185,17,152,241,165,59,
149,66,184,81,47,192,68,80,217,135,218,84,27,163,49,56,
202,24,61,119,2,70,244,77,113,42,137,102,52,184,126,119,
174,27,249,77,26,220,211,67,61,61,101,125,5,146,114,226,
59,160,124,209,71,114,240,123,71,249,58,190,158,104,168,193,
113,167,59,12,238,202,240,123,35,247,133,172,186,184,108,163,
195,80,146,225,48,97,94,15,207,131,97,255,209,147,58,73,
103,168,1,192,60,196,31,234,70,25,28,207,150,28,236,233,
216,44,101,199,191,198,173,86,172,68,240,61,171,195,216,234,
100,97,43,137,38,51,184,247,240,107,135,66,70,130,242,189,
8,57,68,30,159,16,5,46,160,160,14,143,70,216,200,70,
152,141,53,244,239,231,195,21,158,8,48,22,52,212,224,216,
237,23,250,212,1,25,227,103,19,183,69,9,42,76,16,218,
195,94,60,220,230,131,10,139,248,4,164,50,66,158,87,53,
114,172,143,244,253,107,168,80,65,60,81,107,122,58,97,253,
12,141,203,233,40,239,124,252,62,6,101,202,251,10,91,19,
122,8,137,166,36,16,143,254,246,111,36,108,99,12,142,35,
9,212,247,76,148,45,114,24,137,124,173,66,249,119,20,246,
178,225,234,159,62,205,58,63,78,16,202,79,99,156,199,147,
160,37,72,77,209,80,131,43,133,190,158,109,55,133,64,202,
186,132,34,235,196,244,5,231,186,85,67,11,31,197,83,25,
169,27,25,151,100,101,76,224,65,59,217,100,123,55,123,163,
32,33,157,233,24,246,236,141,180,120,17,226,161,232,213,126,
139,223,51,145,255,171,241,155,123,131,78,153,4,229,90,85,
201,245,202,72,43,247,124,145,6,24,220,160,190,118,75,221,
140,50,71,142,104,224,183,26,229,26,245,215,247,208,193,13,
25,127,84,220,30,193,208,159,231,125,221,181,158,66,52,181,
193,17,156,220,34,131,37,207,161,68,26,107,64,135,241,229,
55,119,141,96,104,194,239,234,70,57,159,83,111,86,50,116,
41,5,40,203,249,133,148,169,218,132,116,30,231,33,59,146,
116,73,160,172,57,27,126,97,244,15,139,87,205,193,29,66,
252,252,5,245,230,14,133,35,200,237,241,218,247,29,107,227,
87,158,209,177,142,244,253,220,223,170,149,225,53,189,193,17,
253,137,24,119,137,235,187,151,139,17,5,150,178,213,57,220,
49,63,99,70,203,122,80,158,159,66,128,133,79,218,45,68,
73,117,148,36,93,21,164,19,109,59,214,218,224,168,152,48,
236,215,32,235,74,62,73,226,28,39,124,152,206,63,196,175,
102,160,241,12,216,83,90,145,54,191,168,14,166,157,67,40,
203,91,152,34,240,136,250,170,140,52,244,52,133,151,167,148,
81,23,224,89,1,121,30,112,79,199,54,31,171,214,72,135,
24,23,6,71,240,204,66,196,147,59,193,47,64,224,123,106,
128,239,216,18,234,179,217,158,216,22,168,88,238,190,215,39,
11,151,34,40,238,245,204,179,36,91,21,184,151,181,143,238,
91,63,87,57,244,174,147,167,241,123,47,8,61,146,186,20,
116,18,242,122,16,231,107,217,100,172,155,71,185,235,119,139,
21,124,55,151,86,250,76,143,112,131,84,51,131,163,226,14,
98,120,141,250,185,24,249,46,122,160,47,120,94,150,187,222,
170,166,236,132,214,71,119,232,158,127,115,79,20,113,116,149,
84,87,167,18,177,111,87,227,213,204,184,49,56,130,11,35,
136,139,231,54,150,124,135,70,130,96,121,60,28,140,148,6,
167,206,193,243,98,252,207,217,77,30,36,84,194,13,200,239,
70,146,92,85,129,244,11,158,173,201,202,7,61,14,158,165,
200,227,149,104,89,79,72,219,177,253,208,96,124,69,207,255,
48,161,231,167,253,149,182,180,52,64,196,119,42,226,219,143,
75,228,238,142,123,107,18,221,83,201,182,4,220,111,143,200,
79,213,13,142,58,128,57,246,246,200,203,245,144,127,244,66,
79,46,61,52,208,21,143,188,46,170,26,208,123,110,49,127,
6,133,62,197,42,78,208,187,151,104,44,60,30,144,43,236,
18,93,69,24,87,6,71,232,35,207,187,244,85,71,185,171,
107,99,32,183,181,83,199,241,204,66,73,166,234,144,109,103,
107,33,11,30,68,122,7,104,22,148,240,135,80,194,14,126,
237,14,57,109,88,205,161,139,7,24,149,255,97,47,210,226,
176,147,223,214,189,142,244,11,173,228,86,197,224,88,22,126,
59,135,180,142,129,130,221,87,36,189,28,66,93,220,68,121,
72,52,53,133,30,253,68,28,74,91,6,205,235,197,80,83,
162,169,8,227,206,224,60,112,194,13,97,237,14,234,71,252,
163,122,13,64,5,196,239,77,156,79,72,180,53,67,102,39,
107,67,42,32,207,204,168,133,97,21,66,255,246,237,155,64,
62,5,23,37,242,168,10,171,148,131,73,107,10,26,176,193,
114,141,140,132,186,224,221,230,7,212,251,227,86,253,89,86,
210,250,25,242,224,111,52,40,66,107,120,20,250,88,234,111,
220,26,156,7,221,146,58,202,210,59,229,109,235,110,80,169,
43,117,209,194,243,152,240,216,9,141,218,182,85,111,160,204,
250,11,248,50,136,151,88,140,249,136,247,225,25,51,214,27,
236,214,187,69,30,139,72,35,76,220,114,183,96,160,192,125,
0,245,194,178,47,183,126,10,141,4,143,157,47,244,210,157,
175,38,142,24,107,99,57,238,13,46,8,10,163,175,103,202,
166,3,78,188,135,195,53,180,176,255,3,33,157,64,37,130,
48,247,229,60,2,133,157,84,207,30,166,25,160,223,115,229,
124,238,19,69,234,37,180,244,51,171,185,28,238,30,12,101,
205,129,204,35,123,58,212,203,51,172,167,70,109,159,139,2,
27,111,228,237,79,50,250,241,242,201,213,239,227,161,55,99,
190,13,118,66,25,156,65,52,216,192,192,160,66,95,76,171,
231,161,68,75,82,9,53,155,171,129,181,154,55,113,206,173,
95,238,7,86,137,97,132,175,161,49,156,85,141,85,191,90,
128,121,230,215,8,105,39,54,23,249,94,133,252,94,206,59,
237,196,123,76,48,6,183,142,128,43,158,104,181,15,226,214,
183,190,228,228,205,121,34,23,87,235,196,187,230,224,10,41,
122,138,229,89,244,120,3,221,29,220,9,211,244,163,12,202,
135,103,84,86,83,119,141,193,25,212,13,243,166,79,127,239,
186,54,156,15,195,24,156,129,65,29,97,12,206,192,160,142,
48,6,103,96,80,71,24,131,51,48,168,35,140,193,25,24,
212,17,53,55,56,189,117,198,86,75,171,121,177,161,129,193,
120,5,58,158,77,97,15,243,229,177,250,224,50,48,18,184,
57,213,213,86,179,221,223,6,6,227,5,105,219,218,46,51,
138,107,212,42,2,63,4,69,66,231,175,235,239,96,12,214,
109,240,69,122,218,177,230,102,157,216,30,226,84,27,96,30,
199,207,219,255,154,177,227,251,27,163,51,88,23,193,151,254,
152,187,29,137,142,231,182,106,109,19,43,10,206,225,96,221,
55,129,238,204,216,106,255,108,34,190,11,44,125,154,33,67,
19,153,160,235,223,212,91,234,28,181,56,229,88,243,248,245,
191,152,68,237,193,115,70,144,129,78,88,249,17,105,59,246,
27,67,134,214,5,202,36,226,191,226,157,6,102,116,103,96,
96,96,96,96,96,96,96,96,96,96,96,96,80,67,240,197,
105,54,105,29,64,90,58,202,163,218,42,133,62,201,154,71,
84,32,205,1,219,250,126,165,7,253,232,175,190,19,241,93,
244,69,29,245,92,165,51,48,24,43,160,248,254,69,131,188,
218,75,156,107,138,101,157,157,27,32,93,247,84,43,91,61,
202,247,170,116,231,254,216,180,99,101,10,81,202,177,230,242,
253,83,218,86,123,121,121,70,131,113,133,142,212,192,96,60,
160,153,12,78,111,196,149,188,68,81,218,81,247,234,189,180,
129,155,105,97,112,11,116,164,6,6,227,1,205,106,112,48,
36,222,181,198,27,112,184,185,65,83,202,81,179,217,195,13,
245,108,253,161,172,99,157,158,177,173,203,83,93,241,109,116,
164,6,6,99,1,143,122,227,113,228,188,92,146,115,22,113,
46,10,47,12,122,129,156,19,159,249,73,19,221,169,216,225,
151,165,81,6,199,240,228,167,97,104,166,2,96,111,195,195,
131,72,197,230,97,76,147,105,75,30,222,95,166,193,61,20,
46,71,165,224,94,195,133,48,206,240,9,216,200,207,122,148,
43,243,195,139,40,197,185,34,48,28,195,147,110,45,16,7,
101,194,198,129,60,149,156,194,61,140,70,133,50,13,215,151,
219,216,244,124,136,113,150,171,19,85,3,43,35,101,171,171,
80,49,119,130,110,11,86,184,222,250,226,186,223,153,114,226,
61,226,220,146,181,173,253,196,253,246,108,162,189,11,191,11,
52,143,173,78,246,10,198,194,66,25,46,164,59,148,225,14,
239,187,59,173,52,80,78,237,14,255,1,199,218,141,255,117,
248,174,184,191,121,84,31,51,142,112,174,159,58,155,135,152,
210,253,30,199,217,152,159,81,104,126,91,237,175,153,35,160,
5,109,171,227,209,162,235,11,20,81,22,94,161,188,168,47,
169,190,34,44,26,200,195,190,94,250,3,78,124,7,148,237,
0,252,127,16,97,120,147,203,211,136,227,96,202,100,192,182,
126,12,247,21,136,111,45,126,95,65,207,112,166,167,224,4,
203,228,41,121,159,99,237,10,30,30,37,254,148,184,61,143,
112,167,133,191,61,164,209,240,22,26,248,101,80,166,213,224,
95,131,120,6,40,223,96,61,16,189,221,29,91,34,158,121,
32,125,172,29,202,115,63,126,167,131,127,212,6,135,116,109,
248,235,178,35,158,95,136,115,11,207,232,247,220,121,127,30,
126,231,32,127,111,33,141,235,232,207,58,228,25,163,200,195,
124,228,89,31,240,139,184,30,199,243,169,133,46,242,12,35,
149,136,111,133,52,47,98,56,132,231,65,183,60,110,254,49,
200,121,170,176,180,204,135,49,203,62,199,187,17,183,62,143,
18,60,207,194,237,50,94,62,34,108,26,3,221,109,237,94,
158,161,23,191,132,92,191,130,252,46,5,63,15,180,133,204,
226,231,46,73,108,245,225,76,66,37,145,214,93,240,123,23,
238,171,144,135,91,122,59,90,55,147,104,234,3,100,96,174,
84,208,90,239,118,81,86,56,50,155,21,119,10,244,255,52,
51,160,5,173,11,111,173,160,98,139,208,88,233,79,122,173,
20,10,51,9,124,111,120,225,51,201,246,175,210,125,168,115,
107,42,131,190,172,33,237,196,206,132,145,197,40,108,9,127,
21,121,136,108,50,246,29,63,172,163,94,29,130,18,209,29,
105,242,51,10,215,189,192,157,217,108,141,17,102,161,240,172,
70,57,238,199,239,115,124,198,255,183,82,118,219,215,132,149,
134,114,146,23,31,242,209,11,202,189,187,14,21,131,52,231,
240,55,199,93,251,89,71,74,52,57,6,135,52,250,252,50,
229,144,186,148,173,43,249,217,59,128,231,116,143,15,97,30,
133,188,30,214,255,145,135,126,91,29,171,35,6,120,136,46,
220,34,46,192,84,111,194,221,189,109,102,20,6,7,255,93,
61,62,24,217,105,226,204,6,245,252,64,120,24,163,251,31,
105,220,72,127,252,238,238,213,45,252,95,0,173,192,127,157,
15,252,103,163,93,180,23,234,119,141,248,5,63,222,0,101,
237,248,143,200,195,222,12,60,139,162,120,92,82,47,245,193,
120,116,132,128,222,31,41,126,8,23,125,210,183,173,174,129,
123,222,157,134,144,253,205,195,82,47,117,1,151,148,189,196,
189,94,99,176,163,99,51,100,238,117,40,149,62,157,23,21,
155,166,251,252,201,104,117,244,21,77,218,77,27,33,90,143,
75,229,121,109,166,199,61,166,60,139,222,138,110,94,120,42,
182,118,79,180,199,53,31,220,40,164,7,183,216,98,125,42,
155,132,127,200,27,126,193,237,2,242,121,188,200,139,110,249,
240,124,184,27,175,122,121,105,129,67,82,121,206,188,155,166,
197,99,176,245,185,248,60,220,20,255,239,118,221,213,32,239,
64,32,47,243,37,188,90,121,178,118,108,231,193,68,123,27,
141,102,196,93,173,102,156,186,85,78,170,51,2,238,89,175,
71,71,60,1,131,179,94,227,167,79,247,38,212,103,145,223,
3,65,222,21,76,111,163,204,147,201,175,207,163,100,235,75,
126,180,244,203,33,87,14,151,50,73,235,50,205,139,86,153,
134,166,121,3,87,243,226,255,237,220,255,151,230,61,1,182,
181,212,115,47,104,112,250,162,16,248,217,234,17,143,82,118,
76,43,53,252,75,26,28,248,209,19,168,107,81,134,67,211,
9,235,192,123,58,58,62,134,103,221,120,81,142,204,227,48,
148,149,61,181,132,89,139,248,121,157,85,36,150,79,157,138,
94,203,175,239,181,72,247,10,222,121,144,237,140,109,129,231,
61,217,3,145,47,88,47,40,231,34,142,164,120,7,4,244,
243,120,223,221,177,150,123,101,206,49,56,148,153,189,52,235,
11,245,118,97,128,159,113,93,199,75,61,83,48,108,93,54,
237,174,222,100,185,24,79,93,128,76,76,162,146,184,25,82,
151,209,13,149,180,15,159,169,84,248,229,48,234,53,8,245,
19,44,52,158,221,214,172,91,125,73,135,119,175,24,114,11,
139,112,218,13,221,190,60,235,94,18,191,125,116,71,60,251,
185,207,104,105,228,221,15,132,114,174,118,131,160,120,24,42,
199,213,8,207,225,216,63,17,78,159,131,15,254,19,200,139,
255,28,86,145,119,190,167,236,65,60,56,109,218,250,240,247,
206,206,95,65,101,16,47,166,125,130,235,14,1,59,241,207,
208,45,88,177,240,159,169,25,1,14,117,61,119,80,138,70,
75,119,189,228,110,251,189,202,147,156,195,208,29,241,248,6,
71,165,160,27,161,135,208,232,185,61,63,252,215,13,26,126,
175,227,51,226,122,29,113,110,174,153,129,116,183,181,163,199,
11,5,220,141,13,16,226,214,87,121,129,247,101,240,106,35,
36,6,49,20,66,60,174,210,20,48,184,40,194,200,226,16,
242,225,127,57,6,119,173,87,118,130,247,153,123,126,52,16,
113,134,188,156,143,194,77,78,113,86,231,138,115,30,104,140,
129,240,183,71,29,167,206,58,132,159,219,168,67,62,189,61,
35,67,62,202,19,110,11,36,252,90,232,137,67,247,160,193,
65,159,22,122,115,51,61,53,25,25,181,188,202,43,193,232,
206,17,6,202,182,196,11,83,247,123,227,81,8,221,90,162,
16,143,233,66,57,177,43,244,115,2,115,12,91,105,5,227,
75,82,252,151,119,55,234,37,239,10,221,161,158,246,143,35,
252,43,110,120,117,17,91,106,109,40,104,165,81,145,7,106,
126,219,122,75,20,225,34,62,103,109,245,71,207,96,16,215,
78,110,156,58,253,61,251,191,212,250,69,253,95,143,193,173,
243,180,31,132,195,202,65,252,122,216,197,120,25,54,12,26,
44,120,252,161,44,226,91,19,32,183,183,100,3,130,86,149,
252,72,219,55,56,175,229,39,120,153,162,207,31,122,71,229,
25,0,242,20,105,112,104,65,119,208,140,2,148,227,48,207,
15,113,233,134,3,191,254,229,252,129,252,81,49,252,33,45,
231,34,186,87,149,219,110,80,174,197,58,66,1,135,110,8,
163,21,19,60,133,134,148,175,33,220,149,200,31,47,139,116,
41,169,244,240,30,254,37,13,142,87,15,139,179,6,210,241,
203,9,10,202,214,207,55,202,123,179,176,231,33,155,176,126,
55,194,23,125,63,56,27,32,175,14,241,59,40,206,62,160,
147,39,122,113,100,157,248,15,233,22,52,56,150,81,51,2,
156,226,248,113,65,230,108,192,196,139,117,246,167,145,120,220,
145,71,221,0,3,251,95,201,212,42,247,248,107,245,56,140,
228,21,126,47,7,227,208,189,20,91,110,8,243,15,110,6,
173,185,18,212,107,117,244,88,31,191,43,244,253,223,248,143,
2,45,228,174,11,84,198,235,160,181,28,70,193,109,208,13,
175,126,42,193,91,86,108,223,190,9,220,245,228,31,173,211,
108,240,30,170,195,39,212,175,241,171,123,79,196,251,26,194,
115,136,198,222,118,85,95,129,187,190,169,160,244,151,48,171,
80,142,39,34,169,83,41,242,35,221,146,6,7,57,232,94,
223,3,194,20,53,184,108,87,172,91,51,10,16,143,59,12,
6,33,79,186,23,133,28,189,22,28,147,122,245,84,84,30,
17,231,190,238,240,214,85,102,252,222,174,35,20,208,224,80,
39,238,149,87,133,13,238,177,160,146,5,1,255,114,230,112,
254,34,6,145,73,88,151,248,126,152,139,71,229,27,70,224,
43,124,24,168,211,217,94,120,222,205,39,206,57,24,232,110,
219,146,13,180,164,209,43,206,62,144,63,25,169,48,127,238,
136,170,76,131,123,144,50,19,175,198,26,156,190,157,68,134,
39,200,224,169,40,40,91,173,59,103,184,93,47,47,194,103,
225,239,2,223,98,55,243,110,65,61,192,207,53,18,204,155,
160,4,46,191,109,29,227,246,150,24,107,211,207,86,103,192,
141,215,82,173,162,241,72,80,215,96,29,229,94,172,110,171,
1,240,44,192,47,87,237,28,14,39,24,70,199,231,120,45,
155,186,23,202,21,121,253,48,231,106,224,145,149,60,107,200,
235,69,11,1,113,85,221,224,144,223,239,107,70,23,28,82,
94,235,249,65,201,246,166,35,202,146,118,221,212,191,238,149,
97,78,20,144,246,36,132,247,234,229,225,160,241,200,197,133,
238,28,185,78,6,55,82,7,154,166,139,115,217,64,121,142,
28,137,91,157,29,85,63,114,163,174,94,220,64,250,47,132,
87,119,225,246,103,237,231,54,190,219,209,109,220,25,28,47,
36,68,194,122,50,75,69,146,76,232,59,201,120,209,132,155,
49,245,42,50,143,121,21,38,255,137,216,39,117,64,193,221,
188,54,215,113,123,22,134,135,48,86,115,50,76,63,24,224,
239,93,119,119,110,5,191,76,112,94,64,32,238,95,184,126,
90,153,87,226,247,121,14,89,135,249,122,193,187,67,220,15,
175,78,149,96,108,49,127,128,231,251,17,231,220,197,206,182,
27,195,137,10,174,111,207,68,165,189,11,247,221,92,78,23,
75,144,239,229,78,251,231,228,145,233,86,223,224,96,232,188,
251,156,101,76,57,177,61,144,63,185,98,73,249,115,8,200,
112,166,199,143,70,236,68,111,17,135,112,95,72,43,139,255,
161,144,156,207,242,53,5,227,213,23,15,210,176,220,185,73,
224,230,157,58,25,92,202,105,235,129,187,59,124,180,213,223,
130,198,48,140,186,226,237,54,252,229,115,127,162,189,11,121,
79,33,223,119,245,219,173,122,25,159,247,205,225,89,230,192,
236,197,212,47,40,67,54,236,122,197,90,230,82,136,91,55,
82,186,14,208,80,223,131,186,101,35,139,255,92,33,149,87,
4,214,10,79,254,227,206,224,8,100,96,100,124,206,149,57,
185,207,89,191,191,8,220,1,13,33,244,14,7,20,132,160,
114,193,157,203,195,18,222,122,146,203,243,244,203,58,237,211,
180,224,252,240,234,68,29,40,128,37,238,92,101,228,210,61,
8,92,188,216,123,158,226,187,163,178,189,119,53,60,131,2,
249,114,223,67,129,32,80,221,179,32,108,167,151,95,184,241,
158,110,190,159,185,24,134,127,11,242,245,26,122,153,239,145,
143,0,95,13,12,14,10,129,178,32,205,87,240,27,184,131,
77,65,175,220,22,125,105,87,23,223,51,122,171,117,80,96,
221,179,207,193,239,117,104,40,158,69,35,119,54,249,8,189,
162,230,199,173,243,180,18,188,232,245,117,25,189,5,156,250,
12,41,93,165,247,123,108,228,231,113,132,189,130,50,66,190,
31,0,221,195,185,182,140,90,110,13,196,115,62,195,107,247,
224,60,78,151,7,13,185,109,189,76,185,101,229,181,0,23,
181,224,231,221,245,77,30,222,196,26,144,39,202,46,115,81,
98,92,26,28,4,193,21,50,14,199,64,106,232,153,157,220,
10,164,144,160,172,124,247,166,253,240,255,40,29,32,4,184,
159,236,241,160,210,230,136,115,203,194,214,214,143,192,141,194,
91,137,138,89,57,144,108,75,136,151,15,26,44,132,201,85,
35,55,125,244,92,226,229,9,211,117,183,173,71,217,3,136,
23,141,145,219,149,92,37,76,186,243,50,130,239,104,224,182,
28,126,174,66,146,56,183,179,213,35,168,128,14,97,131,114,
197,126,163,227,5,33,29,223,16,153,71,132,229,66,16,211,
60,79,156,53,32,27,174,160,194,93,221,199,43,139,181,91,
82,247,226,58,30,40,221,97,174,242,121,11,9,80,168,132,
250,45,203,168,35,16,112,129,7,113,160,151,210,134,163,141,
155,74,135,112,124,183,229,47,40,80,254,224,57,154,178,99,
89,65,156,247,97,20,194,197,38,189,138,203,188,220,253,164,
24,214,98,199,217,88,187,185,121,185,167,208,238,12,25,185,
184,124,129,70,16,115,118,206,211,93,247,132,187,18,29,4,
27,25,232,202,105,146,31,175,183,131,33,104,163,56,127,158,
244,112,240,63,18,238,24,101,168,119,184,113,64,7,6,232,
15,247,131,17,246,25,228,79,22,132,24,143,122,21,6,183,
179,176,181,244,99,36,130,248,110,131,187,47,31,214,33,194,
164,216,32,10,155,6,23,170,152,95,151,70,86,73,105,112,
120,230,107,12,202,34,155,99,112,73,117,181,23,102,80,122,
96,131,18,160,64,7,29,203,246,134,106,65,112,152,194,123,
196,168,52,36,190,235,161,242,138,119,77,161,87,106,97,216,
80,152,237,188,151,246,133,192,215,45,28,170,49,143,220,211,
24,84,138,32,120,47,56,21,13,202,218,233,245,102,141,4,
95,235,48,47,146,239,246,133,161,93,38,60,43,135,195,68,
238,10,137,146,59,203,201,70,146,225,25,15,119,17,137,87,
14,56,125,241,228,3,242,231,254,6,6,6,6,6,6,6,
6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
6,6,6,6,19,13,45,45,255,15,75,126,237,110,236,21,
19,8,0,0,0,0,73,69,78,68,174,66,96,130};

unsigned int bootlogo_size(void)
{
	return sizeof(bootlogo);
}

