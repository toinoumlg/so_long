/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 21:47:37 by amalangu          #+#    #+#             */
/*   Updated: 2026/03/13 22:13:48 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include <GLFW/glfw3.h>
#include <stdio.h>

void	key_callback(GLFWwindow *window, int key, int scancode, int action,
		int mode)
{
	t_data	*data;

	data = glfwGetWindowUserPointer(window);
	if (key == GLFW_KEY_W)
		data->player.inputs.w = action;
	if (key == GLFW_KEY_S)
		data->player.inputs.s = action;
	if (key == GLFW_KEY_D)
		data->player.inputs.d = action;
	if (key == GLFW_KEY_A)
		data->player.inputs.a = action;
	if (key == GLFW_KEY_SPACE)
		data->player.inputs.attack = action;
	if (key == GLFW_KEY_ESCAPE)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	(void)scancode;
	(void)mode;
}

void	init_engine(t_data *data)
{
	GLFWwindow	*win;

	glfwInit();
	win = glfwCreateWindow(1280, 720, "so_long", NULL, NULL);
	if (!win)
	{
		glfwTerminate();
		return ;
	}
	glfwMakeContextCurrent(win);
	glfwSetWindowUserPointer(win, data);
	glfwSetKeyCallback(win, key_callback);
	glViewport(0, 0, 1280, 720);
	while (!glfwWindowShouldClose(win))
	{
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(win);
	}
	glfwTerminate();
}
