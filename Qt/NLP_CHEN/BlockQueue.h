#ifndef _BLOCK_QUEUE_H_
#define _BLOCK_QUEUE_H_

#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>

template<class T> 
class BlockQueue {
	public:
		BlockQueue() 
			: queue_()
			  , mutex_()
			  , cond_() {

			  }
		~BlockQueue() { 
		}

		void push(const T& t) {
			{
				std::unique_lock<std::mutex > lock(mutex_);
				queue_.push(t);
			}
			cond_.notify_all();
		}

		T pop() {
			std::unique_lock<std::mutex > lock(mutex_);
			while(queue_.empty()) {
				cond_.wait(lock);	
			}
			
			T front(queue_.front());
			queue_.pop();
			return front;
		}
	
		void clear() {
			std::unique_lock<std::mutex > lock(mutex_);
			while (!queue_.empty()) 
				queue_.pop();	
		}

		size_t size() {
			std::unique_lock<std::mutex > lock(mutex_);
			return queue_.size();	
		}

	private:
		std::queue<T> queue_;
		std::mutex mutex_;
		std::condition_variable cond_;
};

/*template<class T>
class BlockQueue<T* > {
	public:
		BlockQueue()
		: queue_()
		, mutex_()
		, cond_() {
		}
		~BlockQueue(){
			}

		void push(T* t) {
			{
				std::unique_lock<std::mutex> lock(mutex_);
				queue_.push(t);
			}	
			cond_.notify_all();
		}

		T* pop() {
			std::unique_lock<std::mutex> lock(mutex_);
			while( queue_.empty()) {
				cond_.wait(lock);	
			}
			T* front(queue_.front());
			queue_.pop();
			return front;
		}
private:
	std::queue<T* > queue_;
	std::mutex mutex_;
	std::condition_variable cond_;
};
*/

#endif
