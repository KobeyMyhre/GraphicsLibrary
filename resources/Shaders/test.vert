#version 450
		layout(location = 0) in vec4 position;
		layout(location = 2) in vec2 texCoord;
		layout(location = 1) uniform int idx;
		layout(location = 2) uniform int rows = 4;
		layout(location = 3) uniform int cols = 4;
		
		 int r;
		 int c;
		float x;
		float y;
		 vec2 uv;
		out vec2 vUV;
		void main ()
		{ gl_Position = position; 
		
		r = idx / cols;
		c = idx % cols;
		
	

		vUV.xy = (vec2(r,c) + texCoord) / vec2(rows,cols);
		vUV.xy 

		//vUV = texCoord; 
		}