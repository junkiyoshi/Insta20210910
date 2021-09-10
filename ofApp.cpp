#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetLineWidth(0.8);
	ofEnableDepthTest();

	this->line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->line.clear();

	auto radius = 300;
	auto deg_span = 5;

	for (int x = -350; x <= 350; x += 700) {

		for (int deg = 0; deg < 360; deg += deg_span) {

			this->line.addVertex(glm::vec3(x + radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), -radius));
			this->line.addColor(ofColor());
			this->line.addVertex(glm::vec3(x + radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), radius));
			this->line.addColor(ofColor());
		}

		for (int i = 0; i < 800; i++) {

			int z = (int)(ofRandom(radius * 2) + ofGetFrameNum() * ofRandom(1, 3)) % radius * 2 - radius;
			if (x == 350) { z = -z; }
			int deg = (int)ofRandom(0, 360) / deg_span * deg_span;

			this->line.addVertex(glm::vec3(x + radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), z));
			this->line.addColor(ofColor());
		}
	}

	auto color = ofColor();
	for (int i = 0; i < this->line.getNumVertices(); i++) {

		auto location = this->line.getVertex(i);
		auto hue = ofMap(location.x, -600, 600, 0, 255);
		auto alpha = ofMap(location.y, -radius, radius, 255, 32);
		color.setHsb(hue, 255, 255, alpha);
		this->line.setColor(i, color);

		for (int k = i + 1; k < this->line.getNumVertices(); k++) {

			auto other = this->line.getVertex(k);
			float distance = glm::distance(location, other);
			if (distance < 50) {

				this->line.addIndex(i);
				this->line.addIndex(k);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(270);

	this->line.drawWireframe();

	for (int i = 0; i < this->line.getNumVertices(); i++) {

		ofSetColor(this->line.getColor(i));
		ofDrawSphere(this->line.getVertex(i), 4);
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}