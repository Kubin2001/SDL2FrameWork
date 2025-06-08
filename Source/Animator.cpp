#include "Animator.h"
#include "GlobalVariables.h"
#include <iostream>

std::unordered_map<std::string, Animation> Animator::Animations;

void Animator::CreateNew(const std::string& name, const int clipsAmount, const short frameWidth, 
	const short frameHeight, const int frameDelay, const int type) {

	auto mapAnim = Animations.find(name);
	if (mapAnim != Animations.end()) {
		std::cout << "Creation aborted animation " << name << " already exist\n";
		return;
	}

	Animation anim;
	anim.firstFrame = Global::frameCounter;
	anim.frameDelay = frameDelay;
	anim.lastFrame = frameDelay * clipsAmount;
	anim.type = type;
	anim.clips.reserve(clipsAmount);
	int x = 0;
	int y = 0;
	int w = frameWidth;
	int h = frameHeight;
	for (size_t i = 0; i < clipsAmount; i++){
		anim.clips.emplace_back(x,y,w,h);
		x += (frameWidth + 1);
	}

	Animations[name] = anim;
}

SDL_Rect* Animator::Get(const std::string& key) {
	auto mapAnim = Animations.find(key);
	if (mapAnim == Animations.end()) {
		std::cout << "This animation does not exist returned empty rectangle\n";
		return nullptr;
	}
	auto& anim = mapAnim->second;
	int currentFrame = Global::frameCounter - anim.firstFrame;
	switch (anim.type){
		case 0:
			if (currentFrame >= anim.lastFrame) {
				anim.firstFrame = Global::frameCounter;
				return &anim.clips[0];
			}
			return &anim.clips[currentFrame / anim.frameDelay];
		case 1:
			if (currentFrame >= anim.lastFrame) {
				return &anim.clips.back();
			}
			return &anim.clips[currentFrame / anim.frameDelay];

		case 2:
			if (currentFrame >= anim.lastFrame) {
				anim.firstFrame = Global::frameCounter;
				return &anim.clips.back();
			}
			return &anim.clips[(anim.clips.size() -1) - (currentFrame / anim.frameDelay)];

		case 3:
			if (currentFrame >= anim.lastFrame) {
				return &anim.clips[0];
			}
			return &anim.clips[(anim.clips.size() - 1) - (currentFrame / anim.frameDelay)];

		default:
			if (currentFrame >= anim.lastFrame) {
				anim.firstFrame = Global::frameCounter;
				return &anim.clips[0];
			}
			return &anim.clips[currentFrame / anim.frameDelay];
	}
}

Animation* Animator::GetAnim(const std::string& key) {
	auto mapAnim = Animations.find(key);
	if (mapAnim == Animations.end()) {
		std::cout << "This animation does not exist returned nullptr\n";
		return nullptr;
	}
	else {
		return &mapAnim->second;
	}
}

void Animator::Reset(const std::string& key) {
	auto mapAnim = Animations.find(key);
	if (mapAnim == Animations.end()) {
		std::cout << "This animation does not exist: "<<key << " reset aborted\n";
		return;
	}
	mapAnim->second.firstFrame = Global::frameCounter;
}

bool Animator::ClearSingle(const std::string& key) {
	return Animations.erase(key);
}

void Animator::ClearAll() {
	Animations.clear();
}