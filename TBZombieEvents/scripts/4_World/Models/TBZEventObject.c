class TBZEventObject {
	string name;
	vector position;
	vector orientation;
	
	void TBZEventObject(string _name, vector _position, vector _orientation) {
		this.name = _name;
		this.position = _position;
		this.orientation = _orientation;
	}
}