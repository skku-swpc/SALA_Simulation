


# SALA Simulation

## 개요

SALA(Smarphone Assisted Localization Algorithm)은 스마트폰과 IoT 디바이스간의 RSSI(Received Signal Strength Indicator)를 이용하여 IoT 디바이스의 위치를 파악하는 것을 목적으로 한 알고리즘이다.


# 내용

**OMNeT++** 는 가상으로 네트워크 장비들을 배치하고 여러 실험을 할 수 있는 툴이다. SALA에서는 ubuntu에서 4.3.1 버전을 설치하여 사용하였다. 4.3.1 버전을 설치한 후 동봉된 samples, src 폴더를 덮어씌워 사용하면 된다. samples 폴더에 있는 SALA2 프로젝트가 해당 프로젝트이다. ini파일과 ned 파일이 시뮬레이션 설정 코드이며 같은 폴더에 있는 각종 txt 들을 input으로 받아 outlist.txt로 출력한다. omnet++ IDE 실행을 위해서는 터미널에 [omnetpp]라고 치면 된다. 해당 IDE에서 코드 수정과 시뮬레이션 수행을 할 수 있다. 시뮬레이션 수행은 프로젝트 오른쪽 클릭 후 RunAs 에서 선택하면 되는데 OMNeT++ Simulation을 선택할 경우 장비 배치와 패킷 교환 등을 화면상에서 스텝별로 확인할 수 있으며 Local C/C++ Application을 선택 할 경우 txt로 결과값을 출력하게 된다. 실행 설정은 Run Configurations에서 수정할 수 있다. SALA에서는 보통 Run number를 0-29로, Processes to run in parallel을 5로, Userinterface를 Command line으로 설정하여 실행하였다. Run number output 데이터는 한 줄에 세 개의 값이 있으며 차례대로 시간, Device 번호, RSSI 순이다.

**SALA 알고리즘**의 동작을 간략하게 요약하자면 Power-Distance Table을 구성하고 Grid Map을 채운 후에 예상 지점을 도출하는 방식이다. 먼저 average2 함수를 이용해서 centroid 지점을 찾아내고 이를 바탕으로 calcPowerMap 함수에서 Power-Distance Table을 구성한다. 마지막으로 rate2 함수에서 Grid Map을 채우고 비교작업을 통해 예상 지점을 도출한다.


