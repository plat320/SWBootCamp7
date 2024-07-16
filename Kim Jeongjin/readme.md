## M3_MINI_RTOS

`M3_MINI_RTOS` 폴더는 최신 RTOS 코드를 포함하고 있습니다. 이 코드는 기존의 priority queue 기반 스케줄러와 비교했을 때 다음과 같은 개선 사항이 포함되어 있습니다:

- Priority queue의 heap 개선
- Node 중간 삭제 및 업데이트 가능

2024-07-16 10:10 am
- Systick Handler 호출 시 마다 sys_tick 변수 (time stamp) 증가하도록 수정
- timestamp 제대로 시간 반영 되도록 개선
- OS_Block_Task에서 taks_no 받아서 해당 task를 block 상태로 전환할 수 있게 개선
