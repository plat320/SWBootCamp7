## M3_MINI_RTOS

`M3_MINI_RTOS` 폴더는 최신 RTOS 코드를 포함하고 있습니다.
이하의 내용은 해당 코드의 udpate 목록입니다

2024-07-16 09:00 am : M3_MINI_RTOS_02_SCHEDULER_BY_PRIORITY_QUEUE 참조
- Priority queue의 heap 개선
- Node 중간 삭제 및 업데이트 가능

2024-07-16 10:10 am
- Systick Handler 호출 시 마다 sys_tick 변수 (time stamp) 증가하도록 수정
- timestamp 제대로 시간 반영 되도록 개선
- OS_Block_Task에서 taks_no 받아서 해당 task를 block 상태로 전환할 수 있게 개선

2024-07-16 10:57 am : M3_MINI_RTOS_03_Add_Delay_Feature_For_Handling_State_Blocked_Tasks 참조
- OS_Block_Task를 관리하기 위한 blocked_queue를 생성
- systick handler에서 OS_Tick함수를 호출하도록 하여 blocked queue에서 State Blocked 인 task 중 delay시간이 끝난 task만 갱신하도록 수정
- priority_queue에서 compare 함수를 compare_ready와 comapre_blocked로 구분하고 이를 공용으로 사용할 수 있도록 함수 개선
- OS_Scheduler에 Taks 3를 block하는 test code 추가

2024-07-16 11:40 am
- IDLE Task 생성하여 OS_Init 시점에서 생성되도록 수정
- IDLE Task 생성에 맞춰 전체 코드의 task index가 Create 되는 Task와 일치하도록 수정 

2024-07-16 03:58 pm
- task가 delay할 필요가 있을 때 자기 자신을 delay 해야할 시간 만큼 state blocked 할 수 있도록 OS_Block_Current_Task 함수 생성
- CPU를 선점하고 있던 task가 State Blocked로 전환되었을 때, CPU를 즉시 다른 task에게 넘겨주도록 개선
- Systick interrupt 주기를 상수 변수로 바꾸고 systick 값이 Systick Handler 호출 시 해당 변수 만큼 더해지도록 개선
- Systick 변수 타입을 long long int로 변경

2024-07-17 
- Context switching 및 자료구조 변경 시 critical section에 대한 처리 필요[完]
  - BASEPRI 이용하여 구현 완료
- Systick timer를 이용한 delay 함수 개선 필요[完]

2024-07-17 04:02 pm
- 기본적인 동작의 OS_Signal_Send 및 OS_Signal_Wait 함수 구현

2024-07-17 04:51 pm
- Key Value push interrupt를 통해 Task 2에서 push 된 key 값을 Task 3로 Send 하도록 구현

2024-07-18 10:20 am
- Systick_OS_Tick의 위치를 OS.c의 OS_Scheduler_Start 함수 내로 이동
