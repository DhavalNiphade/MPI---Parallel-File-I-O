#include <stdio.h>
#include <hdf5.h>
#include <math.h>
#define PARTICLE_COUNT 10

typedef struct particle2D{
	double x,y,z;
	int type;
} particle_t;

int main(int argc, char** argv){

	double pi = 4.0*atan(1.0);

	particle_t particles[PARTICLE_COUNT];

	for(int i=0 ; i < 10 ; i++){
		particles[i].x = sin(2*pi*i/(PARTICLE_COUNT-1));
		particles[i].y = cos(2*pi*i/(PARTICLE_COUNT-1));
		particles[i].z = 0.1*i;
		particles[i].type = (i >= (PARTICLE_COUNT)/2);
		particles[i].type = (i >= PARTICLE_COUNT/2);
	}

	int mtype = H5Tcreate(H5T_COMPOUND,sizeof(particle_t));
	H5Tinsert(mtype,"x coord",HOFFSET(particle_t,x),H5T_NATIVE_DOUBLE);	
	H5Tinsert(mtype,"y coord",HOFFSET(particle_t,y),H5T_NATIVE_DOUBLE);	
	H5Tinsert(mtype,"z coord",HOFFSET(particle_t,z),H5T_NATIVE_DOUBLE);	
	H5Tinsert(mtype,"particle type",HOFFSET(particle_t,type),H5T_NATIVE_INT);	

	int ftype = H5Tcreate(H5T_COMPOUND,3*sizeof(double)+sizeof(int));
	H5Tinsert(ftype,"x coord",0,H5T_NATIVE_DOUBLE);
	H5Tinsert(ftype,"y coord",sizeof(double),H5T_NATIVE_DOUBLE);
	H5Tinsert(ftype,"z coord",2*sizeof(double),H5T_NATIVE_DOUBLE);
	H5Tinsert(ftype,"particle type",3*sizeof(double),H5T_NATIVE_INT);

	hsize_t dim = PARTICLE_COUNT;
	int space = H5Screate_simple(1,&dim,NULL);

	int fd = H5Fcreate("particles.h5",H5F_ACC_TRUNC,H5P_DEFAULT,H5P_DEFAULT);
	int dset = H5Dcreate(fd,"particle data",mtype,space,H5P_DEFAULT,H5P_DEFAULT,H5P_DEFAULT);

	H5Dwrite(dset, mtype, H5S_ALL, H5S_ALL, H5P_DEFAULT, particles);
	H5Fclose(fd);

	return 0;
}
