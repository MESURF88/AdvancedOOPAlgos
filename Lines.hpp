#ifndef _LINES_H
#define _LINES_H

#include <stdint.h>
#include <string>

class Point
{
public:
	uint8_t my_x;
	uint8_t my_y;
	
	Point(const int x,const int y,const uint32_t line_id = 0) : my_x(x), my_y(y), my_line_id(line_id)
	{
	};

	uint8_t get_x() const
	{
		return my_x;
	}

	uint8_t get_y() const
	{
		return my_y;
	}

	uint32_t get_line_id() const
	{
		return my_line_id;
	}

	void set_line_id(uint32_t id)
	{
		my_line_id = id;
	}

	uint16_t squared_euclidean_distance() const
	{
		// Squared Euclidean distance from the origin.
		const uint16_t x2 = uint16_t(my_x) * my_x;
		const uint16_t y2 = uint16_t(my_y) * my_y;
		return x2 + y2;
	}
	bool operator < (Point const& rhs) const
	{
		return this->squared_euclidean_distance() < rhs.squared_euclidean_distance();
	};
protected:

private:
	uint32_t my_line_id;
};

class Line
{
public:
	int my_id;
	Point my_endpoint1;
	Point my_endpoint2;
	
	Line(const int id, const Point endpoint1, const Point endpoint2) : my_id(id), my_endpoint1(endpoint1), my_endpoint2(endpoint2)
	{
		my_endpoint1.set_line_id(id);
		my_endpoint2.set_line_id(id);
	};

	double point1_to_point2_slope() const
	{
		// slope from point1 to point2
		const double x2 = double(my_endpoint2.my_x) - my_endpoint1.my_x;
		const double y2 = double(my_endpoint2.my_y) - my_endpoint1.my_y;
		return y2 / x2;
	}

	double point2_to_point1_slope() const
	{
		// slope from point2 to point1
		const double x2 = double(my_endpoint1.my_x) - my_endpoint2.my_x;
		const double y2 = double(my_endpoint1.my_y) - my_endpoint2.my_y;
		return y2 / x2;
	}

	int get_id() const
	{
		return my_id;
	}

	bool operator < (Line const& rhs) const
	{
		return this->point1_to_point2_slope() < rhs.point1_to_point2_slope();
	};
protected:

private:

};

#endif
