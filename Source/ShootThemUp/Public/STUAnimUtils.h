#pragma once

#include "Animation/AnimSequenceBase.h"

class STUAnimUtils
{
public:
	template<typename T>
	static T* FindAnimNotifyByClass(const UAnimSequenceBase* const AnimSequence)
	{
		if (!AnimSequence) return nullptr;

		for (const auto& NotifyEvent : AnimSequence->Notifies)
		{
			if (T* Notify = Cast<T>(NotifyEvent.Notify)) return Notify;
		}

		return nullptr;
	}
};