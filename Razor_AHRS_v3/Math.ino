/* This file is part of the Razor AHRS Firmware */


// Computes the dot product of two vectors
float Vector_Dot_Product(const float v1[3], const float v2[3])
{
	float result = 0;

	for (int c = 0; c < 3; c++)
	{
		result += v1[c] * v2[c];
	}

	return result;
}

// Computes the cross product of two vectors
// out has to different from v1 and v2 (no in-place)!
void Vector_Cross_Product(float out[3], const float v1[3], const float v2[3])
{
	out[0] = (v1[1] * v2[2]) - (v1[2] * v2[1]);
	out[1] = (v1[2] * v2[0]) - (v1[0] * v2[2]);
	out[2] = (v1[0] * v2[1]) - (v1[1] * v2[0]);
}

// Multiply the vector by a scalar
void Vector_Scale(float out[3], const float v[3], float scale)
{
	for (int c = 0; c < 3; c++)
	{
		out[c] = v[c] * scale;
	}
}

// Adds two vectors
void Vector_Add(float out[3], const float v1[3], const float v2[3])
{
	for (int c = 0; c < 3; c++)
	{
		out[c] = v1[c] + v2[c];
	}
}

// Multiply two 3x3 matrices: out = a * b
// out has to different from a and b (no in-place)!
void Matrix_Multiply(const float a[3][3], const float b[3][3], float out[3][3])
{
	for (int x = 0; x < 3; x++)  // rows
	{
		for (int y = 0; y < 3; y++)  // columns
		{
			out[x][y] = a[x][0] * b[0][y] + a[x][1] * b[1][y] + a[x][2] * b[2][y];
		}
	}
}

// Multiply 3x3 matrix with vector: out = a * b
// out has to different from b (no in-place)!
void Matrix_Vector_Multiply(const float a[3][3], const float b[3], float out[3])
{
	for (int x = 0; x < 3; x++)
	{
		out[x] = a[x][0] * b[0] + a[x][1] * b[1] + a[x][2] * b[2];
	}
}

// Init rotation matrix using euler angles
// Init rotation matrix using euler angles
void init_rotation_matrix(float m[3][3], float yaw, float pitch, float roll)
{
  float c1 = cos(roll);
  float s1 = sin(roll);
  float c2 = cos(pitch);
  float s2 = sin(pitch);
  float c3 = cos(yaw);
  float s3 = sin(yaw);

  // Euler angles, right-handed, intrinsic, XYZ convention
  // (which means: rotate around body axes Z, Y', X'') 
  m[0][0] = c2 * c3;
  m[0][1] = c3 * s1 * s2 - c1 * s3;
  m[0][2] = s1 * s3 + c1 * c3 * s2;

  m[1][0] = c2 * s3;
  m[1][1] = c1 * c3 + s1 * s2 * s3;
  m[1][2] = c1 * s2 * s3 - c3 * s1;

  m[2][0] = -s2;
  m[2][1] = c2 * s1;
  m[2][2] = c1 * c2;
}

void acceleration_NED(){
  

//////////////////////////////////////////////////////////////////////


  /*SerialPort.print(rotMat[0][0]); SerialPort.print(" ,");
  SerialPort.print(rotMat[0][1]); SerialPort.print(" ,");
  SerialPort.print(rotMat[0][2]); SerialPort.print(" ,");
  SerialPort.print(rotMat[1][0]); SerialPort.print(" ,");
  SerialPort.print(rotMat[1][1]); SerialPort.print(" ,");
  SerialPort.print(rotMat[1][2]); SerialPort.print(" ,");
  SerialPort.print(rotMat[2][0]); SerialPort.print(" ,");
  SerialPort.print(rotMat[2][1]); SerialPort.print(" ,");
  SerialPort.print(rotMat[2][2]); SerialPort.println(" ,"); SerialPort.println(" ");

  int k=0;

  for(int i=0; i<3; ++i){
    for(int j=0; j<3; ++j){
      
      rotMatInv[k] = &rotMat[i][j];
      ++k;
      
      }
    }

  k=0;
    
  MatrixMath RotationInverse;
  RotationInverse.Invert(*rotMatInv, 3);

  
  SerialPort.print("INVERSE: ");
  SerialPort.print(*rotMatInv[0]); SerialPort.print(" ,");
  SerialPort.print(*rotMatInv[1]); SerialPort.print(" ,");
  SerialPort.print(*rotMatInv[2]); SerialPort.print(" ,");
  SerialPort.print(*rotMatInv[3]); SerialPort.print(" ,");
  SerialPort.print(*rotMatInv[4]); SerialPort.print(" ,");
  SerialPort.print(*rotMatInv[5]); SerialPort.print(" ,");
  SerialPort.print(*rotMatInv[6]); SerialPort.print(" ,");
  SerialPort.print(*rotMatInv[7]); SerialPort.print(" ,");
  SerialPort.print(*rotMatInv[8]); SerialPort.println(" ,"); SerialPort.println(" ");
*/
  /*for(int i=0; i<3; ++i){
    for(int j=0; j<3; ++j){
      
      rotMat[i][j] = *rotMatInv[k];
      ++k;
      
      }
    }*/
  
  float a0, a1, a2;
  
  a0 = accel[0];
  a1 = accel[1];
  a2 = accel[2];

  
  aNorth = a0*DCM_Matrix[0][0] + a1*DCM_Matrix[0][1] + a2*DCM_Matrix[0][2];
  aEast = a0*DCM_Matrix[1][0] + a1*DCM_Matrix[1][1] + a2*DCM_Matrix[1][2];
  aDown = a0*DCM_Matrix[2][0] + a1*DCM_Matrix[2][1] + a2*DCM_Matrix[2][2];

  aDown = aDown - GRAVITY;

  aNorth = aNorth / GRAVITY * 9.81;
  aEast = aEast / GRAVITY * 9.81;
  aDown = aDown / GRAVITY * 9.81;

  SerialPort.print(a0); SerialPort.print(", ");
  SerialPort.print(a1); SerialPort.print(", ");
  SerialPort.print(a2); SerialPort.println(", "); SerialPort.println(" ");

  /*aNorth = a0*rotMat[0][0] + a1*rotMat[0][1] + a2*rotMat[0][2];
  aEast = a0*rotMat[1][0] + a1*rotMat[1][1] + a2*rotMat[1][2];
  aDown = a0*rotMat[2][0] + a1*rotMat[2][1] + a2*rotMat[2][2];*/

  SerialPort.print(aNorth); SerialPort.print(", ");
  SerialPort.print(aEast); SerialPort.print(", ");
  SerialPort.print(aDown); SerialPort.println(", "); SerialPort.println(" ");

  delay(300);
  
  }
