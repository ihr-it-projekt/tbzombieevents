class TBZEventObject {
	string name;
	vector position;
	vector orientation;
	
	void TBZEventObject(string name, vector position, vector orientation) {
		this.name = name;
		this.position = position;
		this.orientation = orientation;
	}
}