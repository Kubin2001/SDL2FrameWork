#include "Animator.h"
#include "GlobalVariables.h"
#include <print>

std::unordered_map<std::string, Animation> Animator::Animations;

void Animator::CreateNew(const std::string& name, const int clipsAmount, const short frameWidth, 
	const short frameHeight, const int frameDelay) {

	auto mapAnim = Animations.find(name);
	if (mapAnim != Animations.end()) {
		std::print("Creation aborted animation {} already exist\n", name);
		return;
	}

	Animation anim;
	anim.firstFrame = Global::frameCounter;
	anim.frameDelay = frameDelay;
	anim.lastFrame = frameDelay * clipsAmount;
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
		std::print("This animation does not exist returned empty rectangle\n");
		return nullptr;
	}
	auto& anim = mapAnim->second;
	int currentFrame = Global::frameCounter - anim.firstFrame;
	if (currentFrame >= anim.lastFrame) {
		anim.firstFrame = Global::frameCounter;
		return &anim.clips[0];
	}
	return &anim.clips[currentFrame / anim.frameDelay];

}

void Animator::Reset(const std::string& key) {
	auto mapAnim = Animations.find(key);
	if (mapAnim == Animations.end()) {
		std::print("This animation does not exist reset aborted\n",key);
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