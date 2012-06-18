/*
 * Copyright 2010-2011 Cedric Priscal
 *
 * This file is part of Octopus SDK.
 *
 * Octopus SDK is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * Octopus SDK is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Octopus SDK.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * \file mainpage.h
 * \brief Doxygen documentation file
 */

/**
 * \mainpage
 *
 * <em>Welcome to Octopus SDK !</em>
 *
 * Octopus is a complete C++ framework to develop microcontroler applications.
 *
 * -Cédric
 */

/**
 * \defgroup DEVELOPER_GUIDE Developer Guide
 * \brief 
 * \{
 */

/**
 * \}
 */

/**
 * \defgroup REFERENCE Reference
 * \{
 */

	/**
	 * \defgroup COM_STACK Octopus Communication Stack
	 * \dot
	 *   digraph G {
	 *
     *     ranksep=0.3;
     *
     *     // OSI layers
     *     node [ style="", shape=plaintext, fontsize=9 ];
     *     Layer1         [ label="Layer 1: physical layer", URL="http://en.wikipedia.org/wiki/Physical_layer" ];
     *     Layer2         [ label="Layer 2: data link layer", URL="http://en.wikipedia.org/wiki/Data_link_layer" ];
     *
     *     // Titles
     *     node [ style="", shape=plaintext, fontsize=12 ];
     *     Title1         [ label="Slave device" ];
     *     Title2         [ label="Master device" ];
     *
     *     // Components
     *     node [ style="filled", fillcolor=wheat, shape=component, fontsize=10, width=3 ];
     *     LocalProperty    [ label="LocalProperty",    URL="\ref LocalProperty"    ];
     *     Packet1          [ label="Packet",           URL="\ref Packet"           ];
     *     Usart1           [ label="Usart",            URL="\ref Usart"            ];
     *     RemoteProperty   [ label="RemoteProperty",   URL="\ref RemoteProperty"   ];
     *     Packet2          [ label="Packet",           URL="\ref Packet"           ];
     *     Usart2           [ label="Usart",            URL="\ref Usart"            ];
	 *
     *     { rank=same; Title1; Title2; }
     *     { rank=same; LocalProperty; RemoteProperty; }
     *     { rank=same; Layer2; Packet1; Packet2; }
     *     { rank=same; Layer1; Usart1; Usart2; }
     *
     *     edge [ style=invis ];
     *     Title1 -> LocalProperty;
	 *     Title2 -> RemoteProperty;
     *
     *     edge [ style=solid, arrowhead=odot, fontsize=8 ];
     *     LocalProperty    -> Packet1  [ label="PacketListener", URL="\ref PacketListener" ];
     *     Packet1          -> Usart1   [ label="UsartListener",  URL="\ref UsartListener"  ];
     *     RemoteProperty   -> Packet2  [ label="PacketListener", URL="\ref PacketListener" ];
     *     Packet2          -> Usart2   [ label="UsartListener",  URL="\ref UsartListener"  ];
	 *   }
	 * \enddot
	 */

    /**
     * \defgroup INTERFACES Interfaces
     */

    /**
     * \defgroup LIBS Libraries
     * \{
     */

        /**
         * \defgroup MICROCONTROLLERS Microcontrollers
         * \{
         */

            /**
             * \defgroup AVR_LIBS Atmel AVR ATMEGA328P
             */

        /**
         * \}
         */

        /**
         * \defgroup SENSORS_LIBS Sensors
         */

    /**
     * \}
     */

/**
 * \}
 */
