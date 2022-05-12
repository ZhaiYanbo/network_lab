//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

//	CSMA/CA网络描述

network HybridMAC
{
    parameters:
        double width;	// 网络大小
        double height;
        int dataNodeNum;	// 节点数目
        int queueSize;		// 队列长度
        double rounds;

        double CW_checkInterval;	// 碰撞窗口分时隙长
        int CWmin;					// 碰撞窗口总时长
        double DIFS_checkInterval;	// DIFS分时隙长
        double DIFS;				// DIFS时长
        double data_packet_transmission_time;	// 数据包传输时间
        double conflict_time;
        int retryLimit;				// 数据包冲突后，重传次数限制
        int backoffStageLimit;		// 二进制退避指数限制
        double lamda;				// 数据包产生：泊松分布参数
        double packetSize;			// 数据包大小
        double networkSpeed;		// 网络传输速度

        @display("bgb=115,81");
        
    submodules:
        node[dataNodeNum]: Node{
        }
        
    connections allowunconnected:
        // for i =0..dataNodeNum - 1, for j = 0..dataNodeNum - 1
        // {
        // 	node[i].out[j] --> node[j].in[i] if i != j;
        // }
}