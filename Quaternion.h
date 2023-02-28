#ifndef _QUATERNION_HPP_
#define _QUATERNION_HPP_

class Quaternion {

public:

	Quaternion(tReal a, Vec3f omega) {
		this->s = a;
		this->w = omega;
	}

	Quaternion& operator*=(const tReal x) {
		this->s *= x;
		this->w *= x;
		return (*this);
	}

	Quaternion& operator/=(const tReal x) {
		this->s /= x;
		this->w /= x;
		return (*this);
	}

	Quaternion& operator+=(const Quaternion& q) {
		this->s += q.s;
		this->w += q.w;
		return *this;
	}

	Quaternion operator/(const tReal x) const { return Quaternion(*this) /= x; }
	Quaternion operator*(const tReal x) const { return Quaternion(*this) *= x; }

	Quaternion operator+(const Quaternion q) const { return Quaternion(*this) += q; }
	Quaternion operator*(const Quaternion q) const {
		return Quaternion(s * q.s - (w.dotProduct(q.w)), s * q.w + q.s * w + crossProductMatrix(w) * q.w);
	}

	Mat3f getR() {
		tReal x, y, z;

		x = w.x; y = w.y; z = w.z;

		return Mat3f(
			1 - 2 * y * y - 2 * z * z, 2 * x * y - 2 * s * z, 2 * x * z + 2 * s * y,
			2 * x * y + 2 * s * z, 1 - 2 * x * x - 2 * z * z, 2 * y * z - 2 * s * x,
			2 * x * z - 2 * s * y, 2 * y * z + 2 * s * x, 1 - 2 * x * x - 2 * y * y
		);
	}

	tReal norm() {
		return sqrt(s * s + w.x * w.x + w.y * w.y + w.z * w.z);
	}

	Quaternion normalized() {
		return Quaternion(*this) / norm();
	}


	tReal s;
	Vec3f w;


};


#endif  /* _QUATERNION_HPP_ */